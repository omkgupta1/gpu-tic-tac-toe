#ifndef COMMON_H
#define COMMON_H

#define BOARD_SIZE 9
#define EMPTY ' '
#define PLAYER_X 'X'
#define PLAYER_O 'O'

struct GameState {
    char board[BOARD_SIZE];
    char currentPlayer;
    int moveCount;
};

__host__ __device__ bool isValidMove(char board[], int index) {
    return board[index] == EMPTY;
}

#endif
