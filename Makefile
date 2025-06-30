NVCC = nvcc
SRC = src/main.cpp src/gpu_player1.cu src/gpu_player2.cu src/game.cpp
FLAGS = -std=c++17
TARGET = game

all:
	$(NVCC) $(FLAGS) $(SRC) -o $(TARGET)

clean:
	del /Q game.exe 2>nul || rm -f game
