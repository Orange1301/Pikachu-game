#include "NormalAndHardMode.h"

void NAHGame::SetupGame() {

}

void NAHGame::StartGame(int MODE) {
    switch (MODE) {
        case 2:
            gameBoard.size = 4;
            break;
        case 3:
            gameBoard.size = 8;
            break;
    }

    system("cls");
    gameBoard.Render();
    infoBoard.Render();

    while (true) {
        // xử lý sự kiện nhấn phím
        int key = getch();
        if (key == KEY_UP || key == KEY_W) {
            gameBoard.currentCell.first = (gameBoard.currentCell.first + gameBoard.size - 1) % gameBoard.size;
            gameBoard.Render();
        }
        else if (key == KEY_DOWN || key == KEY_S) {
            gameBoard.currentCell.first = (gameBoard.currentCell.first + 1) % gameBoard.size;
        }
    }
}

void GameBoard::Render() {
    
}

void InfoBoard::Render() {

}