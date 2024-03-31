#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <algorithm> // hàm random_shuffle
#include <vector>    // sử dụng cùng hàm random_suffle để tạo danh sách pokemons ngẫu nhiên
#include <cstdlib>
#include <ctime>
#include "Controller.h"

#define NORMAL 2
#define HARD 3

struct GameBoard
{
    ~GameBoard();

    int size;
    int left, top;
    int remainCells;

    pair<int, int> currentCell = {0, 0};
    pair<int, int> chosenCell1 = {-1, -1};
    pair<int, int> chosenCell2 = {-1, -1};

    char **pokemonsBoard;

    string *backGround;

    void Render();
    void RenderCell(pair<int, int>, int);
    void RemoveCell(pair<int, int>);
    void ReadImage();
};

struct InfoBoard
{
    char playerName[15] = "", mode[8] = "";
    int scores = 0;
    int lives = 3;
    int hints = 3;
    void Render();
    void SaveData();
};

struct NAHGame // NAH = Normal And Hard
{
    static GameBoard gameBoard;
    static InfoBoard infoBoard;

    static void SetupGame(int);
    static void StartGame();

    static vector<pair<int, int>> CheckIMatching(pair<int, int>, pair<int, int>);
    static vector<pair<int, int>> CheckLMatching(pair<int, int>, pair<int, int>);
    static vector<pair<int, int>> CheckUMatching(pair<int, int>, pair<int, int>);
    static vector<pair<int, int>> CheckZMatching(pair<int, int>, pair<int, int>);
    static bool CheckMatching(pair<int, int>, pair<int, int>);

    static void LosingScreen();
    static void WinningScreen();
    static void ExitScreen();
};