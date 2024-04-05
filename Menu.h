#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <random>
#include <fstream>
#include "NormalAndHardMode.h"
#include "DropMode.h"
#include "Controller.h"

#define NORMAL 2
#define HARD 3
#define DROP 4

using namespace std;

struct Menu
{
	static int currentOption;			// Lựa chọn hiện tại
	const static string MainOptions[4]; // Tên các lựa chọn chính
	const static string PlayOptions[4]; // Tên các lựa chọn chơi
	static void MainScreen();			// Màn hình chính
	static void PrintLogo();			// Hiển thị logo

	static void PlayMenu();		  // Menu play
	static void HighScores();	  // Màn hình load file high scores
	static void TutorialScreen(); // Màn hình hướng dẫn cách chơi
	static void ExitScreen();	  // Màn hình thoát trò chơi
	static void GoodbyeScreen();  // Màn hình tạm biệt

	static void NormalMode(); // Chế độ thường
	static void HardMode();	  // Chế độ khó
	static void DropMode();	  // Chế độ rơi

	static void PrintOptionsBoard(const string[]);	// In ra bảng các lựa chọn
	static void PrintAnimation();					// In ra hiệu ứng mở đầu
	static void PrintRectangle(int, int, int, int); // Vẽ hình chữ nhật
};
struct Player		// Dùng để đọc thông tin người chơi từ file HighScores.txt
{
	string playerName;
	string mode;
	int score;
};