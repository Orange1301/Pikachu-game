#include "Controller.h"
#include "Menu.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int main()
{
	Controller::SetUpConsole();
	//Menu::MainScreen();
	Menu::DisplayMenu();
}