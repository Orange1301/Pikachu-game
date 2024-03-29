#pragma once

struct GameBoard {
    // static pair<int, int> currentCell = {0, 0};
    // static pair<int, int> chosenCell1 = {-1, -1};
    // static pair<int, int> chosenCell2 = {-1, -1};

    int size;
    int left, top;
    static void RenderGameBoard();

};

struct InfoBoard {
    char playerName[15] = "", mode[8] = "";
    static void RenderInfoBoard();

};

struct Game {
    GameBoard gameBoard;
    InfoBoard infoBoard;

    Game(int);
    ~Game();    

    static void SetupGame();
    static void StartGame();
};