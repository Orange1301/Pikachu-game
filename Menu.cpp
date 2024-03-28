#include "Menu.h"

int Menu::currentOption = 0;
const string Menu::MainOptions[4] = {"Play", "High Scores", "Tutorial", "Exit"};
const string Menu::PlayOptions[4] = {"Normal Mode", "Hard Mode", "Drop Mode", "Back"};


void Menu::MainScreen() {
	DisplayMenu(MainOptions);
	while(true) {
		int key = getch();
		if (key == KEY_UP || key == KEY_LEFT || key == KEY_W || key == KEY_A)
			MoveMenuCursor(UP);
		else if (key == KEY_DOWN || key == KEY_RIGHT || key == KEY_S || key == KEY_D)
			MoveMenuCursor(DOWN);
		else if (key == KEY_ENTER)
			switch (currentOption) {
				case 0:
					PlayMenu();
					break;
				case 1:
					HighScores();
					break;
				case 2:
			}


	}
}

void Menu::DisplayMenu(string options[])
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
	cout << "Tran Tung Lam - Le Minh";
	Controller::GoToXY(40, 1);
	cout << "21127337 - 21127165";
	Controller::GoToXY(38, 8);
	Controller::SetConsoleColor(BRIGHT_WHITE, GREEN);

	for () {

	}
	
}

void Menu::MoveMenuCursor(int direc) {
    if (direc == UP)
        currentOption = (currentOption + 4) % 5;
    else if (direc == DOWN)
        currentOption = (currentOption + 1) % 5;
    DisplayMenu();
}

void Menu::PlayMenu() {
	DisplayMenu(PlayOptions);
	while(true) {
		int key = getch();
		if (key == KEY_UP || key == KEY_LEFT || key == KEY_W || key == KEY_A)
			MoveMenuCursor(UP);
		else if (key == KEY_DOWN || key == KEY_RIGHT || key == KEY_S || key == KEY_D)
			MoveMenuCursor(DOWN);
		else if (key == KEY_ENTER)
			switch (currentOption) {
				case 0:
					NormalMode();
					break;
				case 1:
					HighScores();
					break;
				case 2:
			}


	}
	
}

void Menu::HighScores() {
	
}