#include "NormalAndHardMode.h"
#include "Menu.h"

void GameBoard::RenderGameBoard() {
    int size, left, top;
    int mode;
    cin >> mode;
    switch (mode) {
    case 2: // NORMAL mode
        size = 4;
        left = 20;
        top = 6;
        break;
    case 3: // HARD mode
        size = 8;
        left = 0;
        top = 0;
        break;
    default:
        return;
    }

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



void InfoBoard::RenderInfoBoard() {
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