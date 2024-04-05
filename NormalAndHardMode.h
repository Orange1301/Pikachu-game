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

#define NORMAL 2
#define HARD 3

struct NAHGameBoard // Bảng game Pokemon
{
    ~NAHGameBoard(); // destructer

    int size;        // Kích thước bảng game
    int left, top;   // Toạ độ góc trên của bảng game
    int remainCells; // Số ô còn lại của bảng game

    pair<int, int> currentCell;                // Toạ độ của ô hiện tại
    pair<int, int> chosenCell1;                // Ô được chọn thứ nhất
    pair<int, int> chosenCell2;                // Ô được chọn thứ 2
    pair<pair<int, int>, pair<int, int>> hint; // Cặp ô gợi ý

    vector<char> pokemonsList; // Danh sách các kí tự Pokemon
    char **pokemonsBoard;      // Mảng 2D chứa thông tin của các ô trong bảng game Pokemon
    char **background;         // Mảng 2D chứa nền của bảng game Pokemon

    void Render();                        // Vẽ bảng game Pokemon
    void RenderCell(pair<int, int>, int); // Vẽ ô trong bảng game Pokemon
    void RemoveCell(pair<int, int>);      // Xoá ô trong bảng game Pokemon
};

struct NAHInfoBoard // Bảng chứa thông tin người chơi
{
    string playerName, mode;
    int score;
    int lives;
    int hints;
    int remainingTime;
    void Render();   // Vẽ bảng thông tin người chơi
    void SaveData(); // Lưu thông tin người chơi
};

struct NAHGame // NAH = Normal And Hard
{
    static NAHGameBoard gameBoard;
    static NAHInfoBoard infoBoard;

    static void SetupGame(int); // thiết lập trò chơi
    static void StartGame();    // bắt đầu trò chơi

    static bool ExistsLine(pair<int, int>, pair<int, int>);                      // Kiểm tra có đường nối giữa 2 ô không
    static vector<pair<int, int>> Path(vector<pair<int, int>>);                  // Vectơ chứa các ô trên đường đi từ ô đầu đến ô cuối trong vectơ đầu vào
    static vector<pair<int, int>> CheckMatching(pair<int, int>, pair<int, int>); // Kiểm tra có đường nối giữa 2 ô không và trả về đường nối (nếu có)
    static pair<pair<int, int>, pair<int, int>> FindPair();                      // Tìm cặp nối hợp lệ và trả về cặp nối đó

    static void LosingScreen(string); // Hiển thị màn hình thua
    static void WinningScreen();      // Hiển thị màn hình thắng
    static void ExitGame();           // Màn hình thoát trò chơi
};