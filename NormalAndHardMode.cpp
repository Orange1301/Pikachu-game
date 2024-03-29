#include "NormalAndHardMode.h"
#include "Menu.h"
GameBoard NAHGame::gameBoard;
InfoBoard NAHGame::infoBoard;
void NAHGame::SetupGame() {

}

void NAHGame::StartGame(int MODE) {
    switch (MODE) {
        case NORMAL:
            gameBoard.size = 4;
            gameBoard.left = 0;
            gameBoard.top = 0;
            break;
        case HARD:
            gameBoard.size = 8;
            gameBoard.left = 0;
            gameBoard.top = 0;
            break;
    }
    gameBoard.remainCells = gameBoard.size * gameBoard.size;
    gameBoard.pokemonsBoard = new char*[size];

    system("cls");
    gameBoard.Render();
    infoBoard.Render();

    while (infoBoard.lives) {
        // xử lý sự kiện nhấn phím
        int key = getch();
        if (key == KEY_UP || key == KEY_W) {
            gameBoard.currentCell.first = (gameBoard.currentCell.first + gameBoard.size - 1) % gameBoard.size;
            // update màu trên board
        }
        else if (key == KEY_DOWN || key == KEY_S) {
            gameBoard.currentCell.first = (gameBoard.currentCell.first + 1) % gameBoard.size;
            // update màu trên board
        }
        else if (key == KEY_LEFT || key == KEY_A) {
            gameBoard.currentCell.second = (gameBoard.currentCell.second + gameBoard.size - 1) % gameBoard.size;
            // update màu trên board
        }
        else if (key == KEY_RIGHT || key == KEY_D) {
            gameBoard.currentCell.second = (gameBoard.currentCell.second + 1) % gameBoard.size;
            // update màu trên board
        }
        else if (key == KEY_ESC) {
            ExitScreen();
        }
        else if (key == KEY_ENTER) {
            if (gameBoard.chosenCell1.first == -1)
                gameBoard.chosenCell1 = gameBoard.currentCell;
            else if (gameBoard.currentCell == gameBoard.chosenCell1)
                gameBoard.chosenCell1 = {-1, -1};
            else {
                gameBoard.chosenCell2 = gameBoard.currentCell;
                if (CheckMatching(gameBoard.chosenCell1, gameBoard.chosenCell2)) {
                    gameBoard.RemoveCell();
                    gameBoard.remainCells -= 2;
                    if (gameBoard.remainCells == 0)
                        WinningScreen();
                    // update board
                    // phát âm thanh
                }
                else {
                    // tô đỏ hai ô được chọn
                    // phát âm thanh
                    gameBoard.chosenCell1 = {-1, -1};
                    gameBoard.chosenCell2 = {-1, -1};
                    infoBoard.lives--;
                    
                }
            }
        }
    }

    LosingScreen();
}

void GameBoard::Render() {
    system("cls");
    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    Controller::GoToXY(left + 1, top);
    putchar(201);
    for (int i = 1; i < size * 6; i++)
    {
        Sleep(5);
        putchar(205);
    }
    putchar(187);
    for (int i = 1; i < size * 3; i++)
    {
        Sleep(10);
        Controller::GoToXY(size * 6 + left + 1, i + top);
        putchar(186);
    }
    Controller::GoToXY(size * 6 + left + 1, size * 3 + top);
    putchar(188);
    for (int i = 1; i < size * 6; i++)
    {
        Controller::GoToXY(size * 6 + left - i + 1, size * 3 + top);
        Sleep(5);
        putchar(205);
    }
    Controller::GoToXY(left + 1, size * 3 + top);
    putchar(200);
    for (int i = 1; i < size * 3; i++)
    {
        Sleep(10);
        Controller::GoToXY(left + 1, size * 3 + top - i);
        putchar(186);
    }
    for (int i = 1; i < size * 3; i++)
    {
        for (int j = 6; j < size * 6; j += 6)
        {
            if (i % 3 != 0)
            {
                Controller::GoToXY(j + left + 1, i + top);
                putchar(179);
            }
        }
        Sleep(10);
    }
    for (int i = 1; i < size * 6; i++)
    {
        for (int j = 3; j < size * 3; j += 3)
        {
            Controller::GoToXY(i + left + 1, j + top);
            if (i % 6 != 0)
                putchar(196);
        }
        Sleep(5);
    }
}

void InfoBoard::Render() {
    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    Menu::PrintRectangle(75, 1, 33, 8);
    Menu::PrintRectangle(75, 10, 33, 12);

    Menu::PrintRectangle(76, 2, 31, 2);
    Controller::SetConsoleColor(BRIGHT_WHITE, RED);
    Controller::GoToXY(84, 3);
    cout << "PLAYER'S INFORMATION";

    Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
    Controller::GoToXY(81, 5);
    cout << "PLayer's name: ";
    Controller::GoToXY(81, 7);
    cout << "Mode: ";

    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    Menu::PrintRectangle(76, 11, 31, 2);
    Controller::SetConsoleColor(BRIGHT_WHITE, RED);
    Controller::GoToXY(85, 12);
    cout << "GAME INFORMATION";
    Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
    Controller::GoToXY(81, 14);
    cout << "Moves:";
    Controller::GoToXY(81, 16);
    cout << "Current score:";
    //Controller::GoToXY(88, 17);
    //cout << score;

    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    Menu::PrintRectangle(75, 23, 33, 2);
    Menu::PrintRectangle(75, 26, 14, 2);
    Menu::PrintRectangle(94, 26, 14, 2);

    Controller::SetConsoleColor(BRIGHT_WHITE, PURPLE);
    Controller::GoToXY(83, 24);
    cout << "M : Move suggestion";
    Controller::SetConsoleColor(BRIGHT_WHITE, GREEN);
    Controller::GoToXY(79, 27);
    cout << "H : Help";
    Controller::SetConsoleColor(BRIGHT_WHITE, YELLOW);
    Controller::GoToXY(97, 27);
    cout << "Esc : Exit";
}

bool NAHGame::CheckIMatching(pair<int, int>, pair<int, int>)
{

}
bool NAHGame::CheckLMatching(pair<int, int>, pair<int, int>)
{

}
bool NAHGame::CheckUMatching(pair<int, int>, pair<int, int>)
{

}
bool NAHGame::CheckZMatching(pair<int, int>, pair<int, int>)
{

}
bool NAHGame::CheckMatching(pair<int, int>, pair<int, int>)
{

}

void GameBoard::RemoveCell()
{

}

void NAHGame::LosingScreen()
{
    system("cls");
    cout << "Đồ thất bại!";
}
void NAHGame::WinningScreen()
{
    system("cls");
    cout << "Thành công!";
}

void NAHGame::ExitScreen()
{

}