#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "Controller.h"
#include "Menu.h"

using namespace std;

int main()
{
	Controller::SetUpConsole();
	Menu::HighScores();
	_getch();
    return 0;
}