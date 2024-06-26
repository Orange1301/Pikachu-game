#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <algorithm> // hàm random_shuffle
#include <vector>    // sử dụng cùng hàm random_suffle để tạo danh sách pokemons ngẫu nhiên
#include <cstdlib>
#include <ctime>
#include <string>
#include "Menu.h"
#include "Controller.h"

struct Node
{
    char pokemon;
    Node *next;
    Node *prev;
};

struct List
{
    Node *head;
    Node *tail;
    int height;
    void Set(int, char);
    char GetPokemon(int);
};

struct DGameBoard
{
    ~DGameBoard();

    int left, top;
    int remainCells;

    pair<int, int> currentCell;
    pair<int, int> chosenCell1;
    pair<int, int> chosenCell2;
    pair<pair<int, int>, pair<int, int>> hint;

    vector<char> pokemonsList;
    List pokemonsBoard[8];
    char **background;

    void Render();
    void RenderColumn(int);
    void RenderCell(pair<int, int>, int);
    void RemoveCell(pair<int, int>);
};

struct DInfoBoard
{
    string playerName, mode;
    int score;
    int lives;
    int hints;
    int remainingTime;
    void Render();
    void SaveData();
};

struct DGame
{
    static DGameBoard gameBoard;
    static DInfoBoard infoBoard;

    static void SetupGame();
    static void StartGame();

    static bool ExistsLine(pair<int, int>, pair<int, int>);
    static vector<pair<int, int>> Path(vector<pair<int, int>>);
    static vector<pair<int, int>> CheckMatching(pair<int, int>, pair<int, int>);
    static pair<pair<int, int>, pair<int, int>> FindPair();

    static void LosingScreen(string);
    static void WinningScreen();
    static void ExitGame();
};