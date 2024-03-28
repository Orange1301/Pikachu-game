#include "Menu.h"

int Menu::currentOption = 0;
const string Menu::options[8] = {"Play", "Normal Mode", "Hard Mode", "Drop Mode", "Tutorial", "High Scores", "Back", "Exit"}

void DisplayMenu() {
    system("cls"); // Xóa màn hình hiện tại
    cout << "<Menu>" //Bà kiếm cái chữ nổi nào đó để xuất ra chỗ này cho đẹp nha
    
}

void Menu::HandleKeyEvent() {
    int key = getch();
    if (key == KEY_UP || key == KEY_LEFT || key == KEY_W || key == KEY_A)
        MoveMenuCursor(UP);
    else if (key == KEY_DOWN || key == KEY_RIGHT || key == KEY_S || key == KEY_D)
        MoveMenuCursor(DOWN);
    else if (key == KEY_ENTER)

}

void Menu::MoveMenuCursor(int direc) {
    if (direc == UP)
        currentOption = (currentOption + 4) % 5;
    else if (direc == DOWN)
        currentOption = (currentOption + 1) % 5;
    DisplayMenu();
}