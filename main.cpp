#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include "Controller.h"
#include "Menu.h"

using namespace std;

int main()
{
	keybd_event(VK_MENU, 0, 0, 0);
	keybd_event(VK_RETURN, 0, 0, 0);
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
	Sleep(500);
	system("color F0");

	srand(time(0));
	Controller::SetUpConsole();
	Menu::MainScreen();
	return 0;
}