#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <unordered_map>
#include <random>
#include <fstream>
#include "Controller.h"
#include "Game.h"

#define NORMAL 4;
#define HARD 8;

using namespace std;

struct Menu
{
	static bool exit;									// cờ thoát game
	static int currentOption;							// lựa chọn hiện tại
	const static string options[5];						// tên các lựa chọn (gồm 5 lựa chọn)
	static void MainScreen();							// màn hình chính
	static void DisplayMenu();							// menu
	static void TutorialScreen();						// màn hình hướng dẫn cách chơi
	static void ExitScreen();							// màn hình thoát trò ch?i
	static void NormalMode();							// chế độ thường
	static void HardMode();								// chế độ khó
	static void PrintLogo();							// in logo
	static void PrintOptionsBoard();					// in ra bảng các lựa chọn
	static void PrintAnimation();						// in ra hiệu ứng mở đầu
	static void PrintRectangle(int, int, int, int);		// vẽ hình chữ nhật
	static void MoveMenuCursor(bool, bool);				// thay đổi lựa chọn
};
struct Player
{
	string playerName;
	int score;
	string mode;
};

