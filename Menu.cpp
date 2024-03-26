#include "Menu.h"

int Menu::CurrentOption;

void DisplayMenu() {
    system("cls"); // Xóa màn hình hiện tại
    cout << "<Menu>" //Bà kiếm cái chữ nổi nào đó để xuất ra chỗ này cho đẹp nha

}

void MoveMenuCursor(int direction) {
    // Kiểm tra xem con trỏ menu có hợp lệ hay không
    if (currentMenuItem >= menuItems.size()) {
        return;
    }

    // Di chuyển con trỏ menu theo hướng được chỉ định
    if (direction == UP) {
        currentMenuItem--;
    } else if (direction == DOWN) {
        currentMenuItem++;
    }

    // Giữ con trỏ menu trong phạm vi hợp lệ
    if (currentMenuItem < 0) {
        currentMenuItem = 0;
    } else if (currentMenuItem >= menuItems.size()) {
        currentMenuItem = menuItems.size() - 1;
    }

    // Hiển thị lại menu với con trỏ được cập nhật
    DisplayMenu();
}