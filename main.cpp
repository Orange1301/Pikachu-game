#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "Controller.h"
#include "Menu.h"

using namespace std;

int main()
{
	SetConsoleOutputCP(65001);
	system("color F0");
	Controller::SetUpConsole();
	Menu::MainScreen();
	_getch();
    return 0;
}