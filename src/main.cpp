#include <iostream>
#include <fstream>
#include <cuda_runtime.h>
#include "../include/game.h"
#include "common.h"

#define PLAYER1_GPU 0
#define PLAYER2_GPU 1

__global__ void gpuChooseMove1(char *board, int *move);  // forward declare
__global__ void gpuChooseMove2(char *board, int *move);

int main() {
    GameState state = {};
    for (int i = 0; i < BOARD_SIZE; ++i) state.board[i] = EMPTY;
    state.currentPlayer = PLAYER_X;
    state.moveCount = 0;

    std::cout << "Starting GPU Tic-Tac-Toe\n";

    while (!checkWinner(state.board, PLAYER_X) && !checkWinner(state.board, PLAYER_O) && !isDraw(state)) {
        int gpu = (state.currentPlayer == PLAYER_X) ? PLAYER1_GPU : PLAYER2_GPU;
        cudaSetDevice(gpu);

        char *d_board;
        int *d_move, h_move = -1;

        cudaMalloc(&d_board, BOARD_SIZE * sizeof(char));
        cudaMemcpy(d_board, state.board, BOARD_SIZE * sizeof(char), cudaMemcpyHostToDevice);
        cudaMalloc(&d_move, sizeof(int));

        if (gpu == PLAYER1_GPU)
            gpuChooseMove1<<<1, 1>>>(d_board, d_move);
        else
            gpuChooseMove2<<<1, 1>>>(d_board, d_move);

        cudaMemcpy(&h_move, d_move, sizeof(int), cudaMemcpyDeviceToHost);
        cudaFree(d_board);
        cudaFree(d_move);

        if (isValidMove(state.board, h_move)) {
            state.board[h_move] = state.currentPlayer;
            ++state.moveCount;
            writeReplay(state.board, state.moveCount);
            state.currentPlayer = (state.currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
        } else {
            std::cout << "Invalid move from GPU " << gpu << ". Skipping turn.\n";
        }

        printBoard(state.board);
    }

    if (checkWinner(state.board, PLAYER_X))
        std::cout << "Player X (GPU 0) wins!\n";
    else if (checkWinner(state.board, PLAYER_O))
        std::cout << "Player O (GPU 1) wins!\n";
    else
        std::cout << "It's a draw!\n";

    return 0;
}
