#include "Menu.h"

int Menu::currentOption = 0;
const string Menu::MainOptions[4] = {"Play", "High Scores", "Tutorial", "Exit"};
const string Menu::PlayOptions[4] = {"Normal Mode", "Hard Mode", "Drop Mode", "Back"};

void Menu::MainScreen() {
	DisplayMenu(MainOptions);
	while(true) {
		// xử lý sự kiện nhấn phím
		int key = getch();
		if (key == KEY_UP || key == KEY_LEFT || key == KEY_W || key == KEY_A) {
			currentOption = (currentOption + 4) % 5;
			DisplayMenu(MainOptions);
		}
		else if (key == KEY_DOWN || key == KEY_RIGHT || key == KEY_S || key == KEY_D) {
			currentOption = (currentOption + 1) % 5;
			DisplayMenu(MainOptions);
		}
		else if (key == KEY_ENTER)
			switch (currentOption) {
				case 0:
					PlayMenu();
					currentOption = 0;
					DisplayMenu(MainOptions);
					break;
				case 1:
					HighScores();
					break;
				case 2:
					TutorialScreen();
					break;
				case 3:
					ExitScreen();
					break;
			}
		else if (key == KEY_ESC)
			ExitScreen();
	}
}

void Menu::DisplayMenu(const string options[])
{
    system("cls"); // Xóa màn hình hiện tại
    unsigned char logo[] = R"(  
                                                                        
		  ,-.----.                  ,--.                                  ,--,               
		  \    /  \     ,---,   ,--/  /|   ,---,         ,----..        ,--.'|               
		  |   :    \ ,`--.' |,---,': / '  '  .' \       /   /   \    ,--,  | :         ,--,  
		  |   |  .\ :|   :  ::   : '/ /  /  ;    '.    |   :     :,---.'|  : '       ,'_ /|  
		  .   :  |: |:   |  '|   '   ,  :  :       \   .   |  ;. /|   | : _' |  .--. |  | :  
		  |   |   \ :|   :  |'   |  /   :  |   /\   \  .   ; /--` :   : |.'  |,'_ /| :  . |  
		  |   : .   /'   '  ;|   ;  ;   |  :  ' ;.   : ;   | ;    |   ' '  ; :|  ' | |  . .  
		  ;   | |`-' |   |  |:   '   \  |  |  ;/  \   \|   : |    '   |  .'. ||  | ' |  | |  
		  |   | ;    '   :  ;|   |    ' '  :  | \  \ ,'.   | '___ |   | :  | ':  | | :  ' ;  
		  :   ' |    |   |  ''   : |.  \|  |  '  '--'  '   ; : .'|'   : |  : ;|  ; ' |  | '  
		  :   : :    '   :  ||   | '_\.'|  :  :        '   | '/  :|   | '  ,/ :  | : ;  ; |  
		  |   | :    ;   |.' '   : |    |  | ,'        |   :    / ;   : ;--'  '  :  `--'   \ 
		  `---'.|    '---'   ;   |,'    `--''           \   \ .'  |   ,/      :  ,      .-./ 
		   `---`            '---'                       `---`    '---'        `--`----'                                                                                                                                                  
	)";
    cout << logo;
    Controller::GoToXY(38, 0);
	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	cout << "Nguyen Ngoc Canh - Le Hong Ngoc";
	Controller::GoToXY(40, 1);
	cout << "23127161 - 23127";
	Controller::GoToXY(38, 8);
	Controller::SetConsoleColor(BRIGHT_WHITE, GREEN);

	// for () {

	// }
	
}

void Menu::PlayMenu() {
	DisplayMenu(PlayOptions);
	while(true) {
		// xử lý sự kiện nhấn phím
		int key = getch();
		if (key == KEY_UP || key == KEY_LEFT || key == KEY_W || key == KEY_A) {
			currentOption = (currentOption + 4) % 5;
			DisplayMenu(PlayOptions);
		}
		else if (key == KEY_DOWN || key == KEY_RIGHT || key == KEY_S || key == KEY_D) {
			currentOption = (currentOption + 1) % 5;
			DisplayMenu(PlayOptions);
		}
		else if (key == KEY_ENTER)
			switch (currentOption) {
				case 0:
					NormalMode();
					break;
				case 1:
					HardMode();
					break;
				case 2:
					DropMode();
					break;
				case 3:
					return;
			}
		else if (key == KEY_ESC)
			return;
	}
}

void Menu::HighScores() {
	
}
void Menu::TutorialScreen() {

}
void Menu::ExitScreen() {

}

void Menu::NormalMode() {
	
}
void Menu::HardMode() {

}
void Menu::DropMode() {

}