#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Controller.h"

#define NORMAL 2
#define HARD 3

struct GameBoard {
    pair<int, int> currentCell = {0, 0};
    pair<int, int> chosenCell1 = {-1, -1};
    pair<int, int> chosenCell2 = {-1, -1};

    int size;
    int left, top;
    int remainCells;

    void Render();
    void RemoveCell();

};

struct InfoBoard {
    char playerName[15] = "", mode[8] = "";
    int scores = 0;
    int lives = 3;
    int hints = 3;
    void Render();

};

struct NAHGame {            // NAH = Normal And Hard
    static GameBoard gameBoard;
    static InfoBoard infoBoard;

    static void SetupGame();
    static void StartGame(int);

    static bool CheckIMatching(pair<int, int>, pair<int, int>);
    static bool CheckLMatching(pair<int, int>, pair<int, int>);
    static bool CheckUMatching(pair<int, int>, pair<int, int>);
    static bool CheckZMatching(pair<int, int>, pair<int, int>);
    static bool CheckMatching(pair<int, int>, pair<int, int>);

    static void LosingScreen();
    static void WinningScreen();
    static void ExitScreen();
};