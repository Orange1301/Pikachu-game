// #include "Menu.h"
// #include "Controller.h"

// struct Node {
//     char pokemon;
//     int height;
//     Node* next;
//     Node* prev;
// };
// struct List {
//     Node* head;
//     Node* tail;
// }:

// struct GameBoard
// {
//     ~GameBoard();

//     int size;
//     int left, top;
//     int remainCells;

//     pair<int, int> currentCell = {0, 0};
//     pair<int, int> chosenCell1 = {-1, -1};
//     pair<int, int> chosenCell2 = {-1, -1};

//     List *pokemonsBoard;
//     char **background;

//     void Render();
//     void RenderCell(pair<int, int>, int);
//     void RemoveCell(pair<int, int>);
// };

// struct InfoBoard
// {
//     string playerName, mode;
//     int score = 0;
//     int lives = 3;
//     int hints = 3;
//     void Render();
//     void SaveData();
// };

// struct DGame
// {
//     static GameBoard gameBoard;
//     static InfoBoard infoBoard;

//     static void SetupGame(int);
//     static void StartGame();

//     static bool ExistsLine(pair<int, int>, pair<int, int>);
//     static vector<pair<int, int>> Path(vector<pair<int, int>>);
//     static vector<pair<int, int>> CheckMatching(pair<int, int>, pair<int, int>);

//     static void LosingScreen();
//     static void WinningScreen();
// }