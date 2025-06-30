#include <curand_kernel.h>
#include "common.h"

__global__ void gpuChooseMove1(char *board, int *move) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    curandState state;
    curand_init(1234, idx, 0, &state);

    int attempt = 0;
    do {
        attempt = curand(&state) % BOARD_SIZE;
    } while (!isValidMove(board, attempt));

    *move = attempt;
}
