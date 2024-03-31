#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include "Controller.h"
#include "Menu.h"

using namespace std;

int main()
{
	// UINT currentCodePage = GetConsoleOutputCP();
	// cout << currentCodePage;
	system("color F0");
	Controller::SetUpConsole();
	Menu::MainScreen();
	_getch();
	// InfoBoard::RenderInfoBoard();
	// GameBoard::RenderGameBoard();
	return 0;
}