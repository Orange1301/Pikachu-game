#include "Controller.h"

HWND Controller::consoleWindow = GetConsoleWindow();
HANDLE Controller::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void Controller::SetUpConsole()		// thiết kế cấu hình cửa sổ console
{
	SetFontInfo();					// thông tin về font chữ cho cửa sổ console
	SetAndCenterWindow();			// căn giữa và thiết lập kích thước cửa sổ console
	DisableMaximize();				// vô hiệu hoá phóng to cửa sổ console
	SetConsoleTitle();				// đặt tiêu đề cho cửa sổ console
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

void Controller::SetConsoleColor(int background, int text)	// thiết lập màu cho văn bản và nền trên cửa sổ console
{
	SetConsoleTextAttribute(consoleOutput, background * 16 + text);
}

void Controller::HideScrollBars()	// ẩn thanh cuộn (scroll bars) trên cửa sổ console
{
	ShowScrollBar(consoleWindow, SB_BOTH, 0);
}

// void Controller::SetConsoleTitle()	// đặt tiêu đề cho cửa sổ console
// {
// 	SetConsoleTitle(L"\u0050\u0049\u004b\u0041\u0043\u0048\u0055"); // PIKACHU
// }

void Controller::DisableMaximize()	// vô hiệu hoá khả năng phóng to cửa sổ console
{
	SetWindowLong(consoleWindow, GWL_STYLE,
		GetWindowLong(consoleWindow, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME));
}

void Controller::ShowCursor(bool show)	// ẩn hoặc hiển thị con trỏ nhấp nháy trên cửa sổ console
{
	CONSOLE_CURSOR_INFO info = { 1, show };
	SetConsoleCursorInfo(consoleOutput, &info);
}

// void Controller::SetFontInfo()	// thiết lập thông tin về font chữ cho cửa sổ console
// {
// 	// 12 - 24
// 	CONSOLE_FONT_INFOEX info;
// 	info.cbSize = sizeof(info);
// 	GetCurrentConsoleFontEx(consoleOutput, FALSE, &info);
// 	info.dwFontSize.X = 12;
// 	info.dwFontSize.Y = 24;
// 	wcscpy_s(info.FaceName, L"Consolas");
// 	SetCurrentConsoleFontEx(consoleOutput, FALSE, &info);
// }

void Controller::ClearConsole()	// xoá nội dung của cửa sổ console
{
	system("cls");
}

void Controller::DisableMouseInput()	// vô hiệu hoá đầu vào từ chuột trong cửa sổ console
{
	DWORD prev_mode;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

int Controller::GetConsoleInput()	// đọc kí tự từ bàn phím và trả về giá trị tương ứng
{
	int c = _getch();
	// Arrow key
	if (c == 0 || c == 224)
	{
		switch (_getch())
		{
		case KEY_UP:				//lên
			return 2;
		case KEY_LEFT:				//trái
			return 3;
		case KEY_RIGHT:				//phải
			return 4;
		case KEY_DOWN:				//xuống
			return 5;
		default:					//nút khác
			return 0;
		}
	}
	else
	{
		if (c == KEY_ESC)					//esc
			return 1;
		else if (c == 87 || c == 119)		//W, w
			return 2;
		else if (c == 65 || c == 97)		//A, a
			return 3;
		else if (c == 68 || c == 100)		//D, d
			return 4;
		else if (c == 83 || c == 115)		//S, s
			return 5;
		else if (c == 13)					//Enter
			return 6;
		else if (c == 72 || c == 104)		//H, h
			return 7;
		else if (c == 77 || c == 109)		// M, m
			return 8;
		else
			return 0;						//nút khác
	}
}

int GetRandomInt(int begin, int end)	// tạo số nguyên ngẫu nhiên
{
	static random_device rd;
	static mt19937 mt(rd());
	uniform_int_distribution<int> dist(0, end);
	return dist(mt);
}