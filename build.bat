@echo off
echo Compiling GPU Tic-Tac-Toe...
nvcc -std=c++17 src\main.cpp src\game.cpp src\gpu_player1.cu src\gpu_player2.cu -o game.exe
if %errorlevel% neq 0 (
    echo Build failed.
) else (
    echo Build successful.
)
pause
