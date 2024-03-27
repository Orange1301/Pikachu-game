#pragma once
#pragma comment(lib, "Winmm.lib");

#include <Windows.h>
#include <conio.h>
#include <vector>
#include <random>
#include <string>

// COLORS (ANSI)
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

// MOVEMENT (ASCII)
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

// SOUNDTRACK
#define MOVE_SOUND 0
#define ENTER_SOUND 1
#define ERROR_SOUND 2
#define WIN_SOUND 4
#define BACKGROUND_SOUND 5
#define EFFECT_SOUND 6

using namespace std;

struct Controller
{
	Controller() {};							// constructer
	~Controller() {};							// destructer
	static HWND consoleWindow;					// con trỏ xử lí cửa sổ console
	static HANDLE consoleOutput;				// con trỏ  xử lí output console
	static void SetUpConsole();					// thiết lập cửa sổ console
	static void GoToXY(int, int);				// di chuyển con trỏ đến vị trí x, y
	static void SetAndCenterWindow();			// căn giữa và thiết lập độ phân giải màn hình console
	static void SetConsoleColor(int, int);		// thiết lập màu chữ và màu nền
	static void HideScrollBars();				// ẩn thanh cuộn
	static void SetConsoleTitle();				// cài đặt tiêu đề console
	static void DisableMaximize();				// vô hiệu hóa phóng to màn hình
	static void ShowCursor(bool);				// ẩn hoặc hiện con trỏ
	static void SetFontInfo();					// cài đặt font chữ
	static void ClearConsole();					// xóa màn hình console
	static void DisableMouseInput();			// vô hiệu hoá con chuột trong console
	static int GetConsoleInput();				// lấy lệnh từ bàn phím
	static void PlaySound(int);					// phát âm thanh
};

int GetRandomInt(int begin, int end);			// hàm lấy số nguyên ngẫu nhiên