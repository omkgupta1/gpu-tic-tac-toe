#include "common.h"

__global__ void gpuChooseMove2(char *board, int *move) {
    // Simple strategy: pick the first valid move
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (isValidMove(board, i)) {
            *move = i;
            return;
        }
    }
    *move = -1;
}
