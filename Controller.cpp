#include "Controller.h"

HWND Controller::consoleWindow = GetConsoleWindow();
HANDLE Controller::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void Controller::SetUpConsole()		// thiết kế cấu hình cửa sổ console
{
	SetAndCenterWindow();			// căn giữa và thiết lập kích thước cửa sổ console
	DisableMaximize();				// vô hiệu hoá phóng to cửa sổ console
	// SetConsoleTitle();				// đặt tiêu đề cho cửa sổ console
	HideScrollBars();				// ẩn thanh cuộn trên cửa sổ console
	ShowCursor(false);				// ẩn con trỏ trên của sổ console
	DisableMouseInput();			// vô hiệu hoá đầu vào từ chuột
}

void Controller::GoToXY(int x, int y)	// di chuyển con trỏ đến vị trí cụ thể có toạ độ (x;y) trên cửa sổ console
{
	SetConsoleCursorPosition(consoleOutput, COORD{ (short)x, (short)y });
}

void Controller::SetAndCenterWindow()	// căn giữa cửa sổ console và thiết lập kích thước của nó
{
	RECT rectClient, rectWindow;
	GetClientRect(consoleWindow, &rectClient), GetWindowRect(consoleWindow, &rectWindow);
	int width = 1100;
	int height = 768;
	int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	int posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
}

void Controller::DisableMaximize()	// vô hiệu hoá khả năng phóng to cửa sổ console
{
	SetWindowLong(consoleWindow, GWL_STYLE,
		GetWindowLong(consoleWindow, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME));
}

void Controller::HideScrollBars()	// ẩn thanh cuộn (scroll bars) trên cửa sổ console
{
	ShowScrollBar(consoleWindow, SB_BOTH, 0);
}

void Controller::ShowCursor(bool show)	// ẩn hoặc hiển thị con trỏ nhấp nháy trên cửa sổ console
{
	CONSOLE_CURSOR_INFO info = { 1, show };
	SetConsoleCursorInfo(consoleOutput, &info);
}

void Controller::DisableMouseInput()	// vô hiệu hoá đầu vào từ chuột trong cửa sổ console
{
	DWORD prev_mode;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

void Controller::SetConsoleColor(int background, int text)	// thiết lập màu cho văn bản và nền trên cửa sổ console
{
	SetConsoleTextAttribute(consoleOutput, background * 16 + text);
}



// int GetRandomInt(int begin, int end)	// tạo số nguyên ngẫu nhiên
// {
// 	static random_device rd;
// 	static mt19937 mt(rd());
// 	uniform_int_distribution<int> dist(0, end);
// 	return dist(mt);
// }