#include "Controller.h"

HWND Controller::consoleWindow = GetConsoleWindow();
HANDLE Controller::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void Controller::SetUpConsole()		// thiết kế cấu hình cửa sổ console
{
	SetAndCenterWindow();			// căn giữa và thiết lập kích thước cửa sổ console
	// SetConsoleTitle();			// đặt tiêu đề cho cửa sổ console
	ShowCursor(false);				// ẩn con trỏ trên của sổ console
}

void Controller::GoToXY(int x, int y)	// di chuyển con trỏ đến vị trí cụ thể có toạ độ (x;y) trên cửa sổ console
{
	SetConsoleCursorPosition(consoleOutput, COORD{ (short)x, (short)y });
}

// void Controller::SetAndCenterWindow()	// căn giữa cửa sổ console và thiết lập kích thước của nó
// {
// 	RECT rectClient, rectWindow;
// 	GetClientRect(consoleWindow, &rectClient), GetWindowRect(consoleWindow, &rectWindow);
// 	int width = 1100;
// 	int height = 1500;
// 	int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
// 	int posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
// 	MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
// }

void Controller::ShowCursor(bool show)	// ẩn hoặc hiển thị con trỏ nhấp nháy trên cửa sổ console
{
	CONSOLE_CURSOR_INFO info = { 1, show };
	SetConsoleCursorInfo(consoleOutput, &info);
}

void Controller::SetConsoleColor(int background, int text)	// thiết lập màu cho văn bản và nền trên cửa sổ console
{
	SetConsoleTextAttribute(consoleOutput, background * 16 + text);
}
