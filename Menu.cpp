#include "Menu.h"

int Menu::currentOption = 0;
const string Menu::options[9] = {"Play", "High Scores", "Tutorial", "Exit", "Normal Mode", "Hard Mode", "Drop Mode", "Back", "Exit"};

void Menu::DisplayMenu()
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
}

// void Menu::HandleKeyEvent() {
//     int key = getch();
//     if (key == KEY_UP || key == KEY_LEFT || key == KEY_W || key == KEY_A)
//         MoveMenuCursor(UP);
//     else if (key == KEY_DOWN || key == KEY_RIGHT || key == KEY_S || key == KEY_D)
//         MoveMenuCursor(DOWN);
//     else if (key == KEY_ENTER)

// }

// void Menu::MoveMenuCursor(int direc) {
//     if (direc == UP)
//         currentOption = (currentOption + 4) % 5;
//     else if (direc == DOWN)
//         currentOption = (currentOption + 1) % 5;
//     DisplayMenu();
// }