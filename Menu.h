#pragma once
#include <iostream>
#include <string>
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
	static void mainScreen();							// màn hình chính
	static void menu();									// menu
	static void tutorialScreen();						// màn hình hướng dẫn cách chơi
	static void exitScreen();							// màn hình thoát trò ch?i
	static void normalMode();							// chế độ thường
	static void hardMode();								// chế độ khó
	static void printLogo();							// in logo
	static void printOptionsBoard();					// in ra bảng các lựa chọn
	static void printAnimation();						// in ra hiệu ứng mở đầu
	static void printRectangle(int, int, int, int);		// vẽ hình chữ nhật
	static void changeOption(bool, bool);				// thay đổi lựa chọn
};
struct Player
{
	string playerName;
	int score;
	string mode;
};

