#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <random>
#include <fstream>
// #include "Game.h"
#include "Controller.h"

#define NORMAL 4;
#define HARD 8;

using namespace std;

struct Menu
{
	static bool exit;									// cờ thoát game
	static int currentOption;							// lựa chọn hiện tại
	const static string options[9];						// tên các lựa chọn
	static void MainScreen();							// màn hình chính
	static void HandleKeyEvent();						// kiểm tra sự kiện nhấn phím
	static void MoveMenuCursor(int);					// thay đổi menu cursor
	static void MainMenu();								// menu
	static void PlayMenu();								// menu play
	static void HighScores();							// màn hình load file high scores
	static void TutorialScreen();						// màn hình hướng dẫn cách chơi
	static void ExitScreen();							// màn hình thoát trò chơi
	static void NormalMode();							// chế độ thường
	static void HardMode();								// chế độ khó
	static void DropMode();								// chế độ rơi
	static void DisplayMenu();							// in logo
	static void GoBack() {};							// trở về menu
	static void PrintOptionsBoard();					// in ra bảng các lựa chọn
	static void PrintAnimation();						// in ra hiệu ứng mở đầu
	static void PrintRectangle(int, int, int, int);		// vẽ hình chữ nhật
	static void ChangeOption(bool, bool);				// thay đổi lựa chọn
};
struct Player
{
	string playerName;
	int score;
	string mode;
};