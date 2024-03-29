#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <random>
#include <fstream>
#include "NormalAndHardMode.h"
#include "Controller.h"

#define NORMAL 2
#define HARD 3
#define DROP 4

using namespace std;

struct Menu
{
	static int currentOption;				 // lựa chọn hiện tại
	const static string MainOptions[4];		 // tên các lựa chọn chính
	const static string PlayOptions[4];		 // tên các lựa chọn chơi
	static void MainScreen();				 // màn hình chính
	static void PrintLogo();				 // hiển thị logo

	static void PlayMenu();		  // menu play
	static void HighScores();	  // màn hình load file high scores
	static void TutorialScreen(); // màn hình hướng dẫn cách chơi
	static void ExitScreen();	  // màn hình thoát trò chơi

	static void NormalMode(); // chế độ thường
	static void HardMode();	  // chế độ khó
	static void DropMode();	  // chế độ rơi

	static void PrintOptionsBoard(const string[]);	// in ra bảng các lựa chọn
	static void PrintAnimation();					// in ra hiệu ứng mở đầu
	static void PrintRectangle(int, int, int, int); // vẽ hình chữ nhật
};
struct Player		// dùng để đọc thông tin người chơi từ file HighScores.txt
{
	string playerName;
	string mode;
	int score;
};