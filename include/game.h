#ifndef GAME_H
#define GAME_H

#include "common.h"

void printBoard(const char board[]);
bool checkWinner(const char board[], char player);
bool isDraw(const GameState& state);
void writeReplay(const char board[], int moveNumber);

#endif
