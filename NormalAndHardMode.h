#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <Controller.h>

#define NORMAL 2;
#define HARD 3;

struct GameBoard {
    pair<int, int> currentCell = {0, 0};
    pair<int, int> chosenCell1 = {-1, -1};
    pair<int, int> chosenCell2 = {-1, -1};

    int size;
    int left, top;

    void Render();

};

struct InfoBoard {
    char playerName[15] = "", mode[8] = "";
    int scores;
    void Render();

};

struct NAHGame {
    static GameBoard gameBoard;
    static InfoBoard infoBoard;

    static void SetupGame();
    static void StartGame(int);
};