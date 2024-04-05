#include "Controller.h"

HWND Controller::consoleWindow = GetConsoleWindow();
HANDLE Controller::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void Controller::SetUpConsole() // Thiết kế cấu hình cửa sổ console
{
	ShowCursor(false);	  // Ẩn con trỏ trên của sổ console
	SetAndCenterWindow(); // Căn giữa và thiết lập kích thước cửa sổ console
	DisableMaximize();	  // Vô hiệu hoá phóng to màn hình
	HideScrollBars();	  // Ẩn thanh cuộn
}

void Controller::GoToXY(int x, int y) // Di chuyển con trỏ đến vị trí cụ thể có toạ độ (x;y) trên cửa sổ console
{
	SetConsoleCursorPosition(consoleOutput, COORD{(short)x, (short)y});
}

void Controller::SetAndCenterWindow() // Căn giữa cửa sổ console và thiết lập kích thước của nó
{
	RECT rectClient, rectWindow;
	GetClientRect(consoleWindow, &rectClient), GetWindowRect(consoleWindow, &rectWindow);
	int width = 1200;
	int height = 800;
	int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	int posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
}

void Controller::ShowCursor(bool show) // Ẩn hoặc hiển thị con trỏ nhấp nháy trên cửa sổ console
{
	CONSOLE_CURSOR_INFO info = {1, show};
	SetConsoleCursorInfo(consoleOutput, &info);
}

void Controller::SetConsoleColor(int background, int text) // Thiết lập màu cho văn bản và nền trên cửa sổ console
{
	SetConsoleTextAttribute(consoleOutput, background * 16 + text);
}

void Controller::DisableMaximize() // Vô hiệu hoá phóng to cửa sổ console
{
	SetWindowLong(consoleWindow, GWL_STYLE,
				  GetWindowLong(consoleWindow, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME));
}

void Controller::HideScrollBars() // Ẩn thanh cuộn trên cửa sổ console
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size = {
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1};
	SetConsoleScreenBufferSize(handle, new_size);
}