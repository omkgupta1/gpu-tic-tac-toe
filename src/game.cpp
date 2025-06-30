#include <iostream>
#include <fstream>
#include "../include/game.h"

void printBoard(const char board[]) {
    std::cout << "\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << (board[i] == EMPTY ? '.' : board[i]);
        if ((i + 1) % 3 == 0) std::cout << "\n";
        else std::cout << " ";
    }
    std::cout << "\n";
}

bool checkWinner(const char board[], char player) {
    const int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, // rows
        {0,3,6}, {1,4,7}, {2,5,8}, // cols
        {0,4,8}, {2,4,6}           // diags
    };
    for (auto &win : wins) {
        if (board[win[0]] == player && board[win[1]] == player && board[win[2]] == player)
            return true;
    }
    return false;
}

bool isDraw(const GameState& state) {
    return state.moveCount >= BOARD_SIZE;
}

void writeReplay(const char board[], int moveNumber) {
    std::ofstream log("replay/replay_log.txt", std::ios::app);
    log << "Move " << moveNumber << ":\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        log << (board[i] == EMPTY ? '.' : board[i]);
        if ((i + 1) % 3 == 0) log << "\n";
        else log << " ";
    }
    log << "\n";
    log.close();
}
