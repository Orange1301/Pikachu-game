#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "Controller.h"
#include "Menu.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100

#define KEY_ENTER 13
#define KEY_ESC 27

using namespace std;

int main()
{
	Controller::SetUpConsole();
	//Menu::MainScreen();
	Menu::DisplayMenu();
	getch();
    return 0;
}