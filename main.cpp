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

	// ifstream f[51];
    // int i = 1;
    // string fname;
	// for (int i = 1; i < 52; i++)
	// 	f[i].open("Frames/" + to_string(i) + ".txt");
    // while (true)
    // {
    //     string line;
    //     Controller::GoToXY(0, 0);
    //     while (getline(f[i], line))
    //         cout << line << endl;
    //     Sleep(30);
    //     if (++i == 53) i = 1;
	// 	if (kbhit()) break;
    // }
	// for (int i = 1; i < 52; i++)
	// 	f[i].close();

	srand(time(0));
	Controller::SetUpConsole();
	Menu::MainScreen();
	return 0;
}