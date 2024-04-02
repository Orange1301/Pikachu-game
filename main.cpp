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
	// SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	// SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	keybd_event(VK_MENU, 0, 0, 0);
	keybd_event(VK_RETURN, 0, 0, 0);
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
	Sleep(500);
	system("color F0");
	Controller::SetUpConsole();
	Menu::MainScreen();
	_getch();
	// InfoBoard::RenderInfoBoard();
	// GameBoard::RenderGameBoard();
	return 0;
}