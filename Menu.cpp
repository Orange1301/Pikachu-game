#include "Menu.h"

int Menu::currentOption = 0;
const string Menu::options[9] = {"Play", "High Scores", "Tutorial", "Exit", "Normal Mode", "Hard Mode", "Drop Mode", "Back", "Exit"};

void DisplayMenu() {
    system("cls"); // Xóa màn hình hiện tại
    cout << "<Menu>" //Bà kiếm cái chữ nổi nào đó để xuất ra chỗ này cho đẹp nha
    
}

void MoveMenuCursor(int direc) {
    if (direc == UP || direc = LEFT)
        currentOption = (currentOption + 4) % 5;
    else if (direc == DOWN || direc == RIGHT)
        currentOption = (currentOption + 1) % 5;
    DisplayMenu();
}