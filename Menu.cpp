#include "Menu.h"

int Menu::currentOption = 0;
const string Menu::MainOptions[4] = {"Play", "High Scores", "Tutorial", "Exit"};
const string Menu::PlayOptions[4] = {"Normal Mode", "Hard Mode", "Drop Mode", "Back"};

using namespace std;

void Menu::MainScreen()
{
	PrintAnimation();
	PrintLogo();
	PrintOptionsBoard(MainOptions);
	while (true)
	{
		// xử lý sự kiện nhấn phím
		int key = _getch();
		if (key == KEY_UP || key == KEY_LEFT || key == KEY_W || key == KEY_A)
		{
			currentOption = (currentOption + 3) % 4;
			PrintOptionsBoard(MainOptions);
		}
		else if (key == KEY_DOWN || key == KEY_RIGHT || key == KEY_S || key == KEY_D)
		{
			currentOption = (currentOption + 1) % 4;
			PrintOptionsBoard(MainOptions);
		}
		else if (key == KEY_ENTER)
			switch (currentOption)
			{
			case 0:
				PlayMenu();
				currentOption = 0;
				PrintOptionsBoard(MainOptions);
				break;
			case 1:
				HighScores();
				PrintLogo();
				PrintOptionsBoard(MainOptions);
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

void Menu::PrintAnimation()
{
	const string logo[7] = {
		R"(
		  ,-.----.
		  \    /  \
		  |   :    \
		  |   |  .\ :
		  .   :  |: |
		  |   |   \ :
		  |   : .   /
		  ;   | |`-' 
		  |   | ;
		  :   ' |
		  :   : :
		  |   | :
		  `---'.|
		    `---`

			  		PRESS ANY KEY FROM KEYBOARD TO CONTINUE   
		)",
		R"(
		  ,-.----.
		  \    /  \     ,---,
		  |   :    \ ,`--.' |
		  |   |  .\ :|   :  :
		  .   :  |: |:   |  '
		  |   |   \ :|   :  |
		  |   : .   /'   '  ;
		  ;   | |`-' |   |  |
		  |   | ;    '   :  ;
		  :   ' |    |   |  '
		  :   : :    '   :  |
		  |   | :    ;   |.' 
		  `---'.|    '---'   
		    `---`

			  		PRESS ANY KEY FROM KEYBOARD TO CONTINUE
		)",
		R"(
		  ,-.----.                  ,--.
		  \    /  \     ,---,   ,--/  /|
		  |   :    \ ,`--.' |,---,': / '
		  |   |  .\ :|   :  ::   : '/ / 
		  .   :  |: |:   |  '|   '   ,  
		  |   |   \ :|   :  |'   |  /   
		  |   : .   /'   '  ;|   ;  ;   
		  ;   | |`-' |   |  |:   '   \  
		  |   | ;    '   :  ;|   |    ' 
		  :   ' |    |   |  ''   : |.  \
		  :   : :    '   :  ||   | '_\.'
		  |   | :    ;   |.' '   : |
		  `---'.|    '---'   ;   |,'
		    `---`            '---'

					PRESS ANY KEY FROM KEYBOARD TO CONTINUE
		)",
		R"(
		  ,-.----.                  ,--.               
		  \    /  \     ,---,   ,--/  /|   ,---,       
		  |   :    \ ,`--.' |,---,': / '  '  .' \      
		  |   |  .\ :|   :  ::   : '/ /  /  ;    '.    
		  .   :  |: |:   |  '|   '   ,  :  :       \   
		  |   |   \ :|   :  |'   |  /   :  |   /\   \  
		  |   : .   /'   '  ;|   ;  ;   |  :  ' ;.   : 
		  ;   | |`-' |   |  |:   '   \  |  |  ;/  \   \
		  |   | ;    '   :  ;|   |    ' '  :  | \  \ ,'
		  :   ' |    |   |  ''   : |.  \|  |  '  '--'  
		  :   : :    '   :  ||   | '_\.'|  :  :
		  |   | :    ;   |.' '   : |    |  | ,'
		  `---'.|    '---'   ;   |,'    `--''
		    `---`            '---'

					PRESS ANY KEY FROM KEYBOARD TO CONTINUE
		)",
		R"(
		  ,-.----.                  ,--.                          
		  \    /  \     ,---,   ,--/  /|   ,---,         ,----..  
		  |   :    \ ,`--.' |,---,': / '  '  .' \       /   /   \ 
		  |   |  .\ :|   :  ::   : '/ /  /  ;    '.    |   :     :
		  .   :  |: |:   |  '|   '   ,  :  :       \   .   |  ;. /
		  |   |   \ :|   :  |'   |  /   :  |   /\   \  .   ; /--` 
		  |   : .   /'   '  ;|   ;  ;   |  :  ' ;.   : ;   | ;    
		  ;   | |`-' |   |  |:   '   \  |  |  ;/  \   \|   : |    
		  |   | ;    '   :  ;|   |    ' '  :  | \  \ ,'.   | '___ 
		  :   ' |    |   |  ''   : |.  \|  |  '  '--'  '   ; : .'|
		  :   : :    '   :  ||   | '_\.'|  :  :        '   | '/  :
		  |   | :    ;   |.' '   : |    |  | ,'        |   :    /
		  `---'.|    '---'   ;   |,'    `--''           \   \ .'
		    `---`            '---'                       `---`

					PRESS ANY KEY FROM KEYBOARD TO CONTINUE
		)",
		R"(
		  ,-.----.                  ,--.                                  ,--,
		  \    /  \     ,---,   ,--/  /|   ,---,         ,----..        ,--.'|
		  |   :    \ ,`--.' |,---,': / '  '  .' \       /   /   \    ,--,  | :
		  |   |  .\ :|   :  ::   : '/ /  /  ;    '.    |   :     :,---.'|  : '
		  .   :  |: |:   |  '|   '   ,  :  :       \   .   |  ;. /|   | : _' |
		  |   |   \ :|   :  |'   |  /   :  |   /\   \  .   ; /--` :   : |.'  |
		  |   : .   /'   '  ;|   ;  ;   |  :  ' ;.   : ;   | ;    |   ' '  ; :
		  ;   | |`-' |   |  |:   '   \  |  |  ;/  \   \|   : |    '   |  .'. |
		  |   | ;    '   :  ;|   |    ' '  :  | \  \ ,'.   | '___ |   | :  | '
		  :   ' |    |   |  ''   : |.  \|  |  '  '--'  '   ; : .'|'   : |  : ;
		  :   : :    '   :  ||   | '_\.'|  :  :        '   | '/  :|   | '  ,/
		  |   | :    ;   |.' '   : |    |  | ,'        |   :    / ;   : ;--'
		  `---'.|    '---'   ;   |,'    `--''           \   \ .'  |   ,/
		    `---`            '---'                       `---`    '---'

			  		PRESS ANY KEY FROM KEYBOARD TO CONTINUE
		)",
		R"(
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

					PRESS ANY KEY FROM KEYBOARD TO CONTINUE
		)"};
	int color[] = {YELLOW, GREEN, AQUA, LIGHT_BLUE, BLUE, LIGHT_PURPLE, PURPLE};
	while (1)
	{
		bool flag = 1;
		for (int i = 0; i < 7; i++)
		{
			Controller::GoToXY(0, 0);
			Controller::SetConsoleColor(BRIGHT_WHITE, color[i]);
			cout << logo[i];
			Sleep(200);
			if (_kbhit())
			{
				int key = _getch();
				flag = 0;
				break;
			}
		}
		system("cls");
		if (flag == 0)
		{
			break;
		}
	}
}

void Menu::PrintLogo()
{
	Controller::GoToXY(0, 0);
	Controller::SetConsoleColor(BRIGHT_WHITE, RED);
	cout << R"(                                                                 
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
	Controller::GoToXY(0, 18);
	SetConsoleOutputCP(65001);
	cout << R"(
                                                                                                ⠀⠀⠀⠀⠀⠀⠀⣠⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                                ⠀⠀⠀⠀⠀⠀⣰⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                                ⠀⠀⠀⠀⠀⢠⠋⠁⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                                ⠀⠀⠀⠀⠀⡆⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                                ⠀⠀⠀⠀⢠⠁⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠤⠀⠒⣶⣶⡶⠂⠀
                                                                                                ⠀⠀⠀⠀⢸⢀⠠⠔⠒⠒⠒⠒⠂⠤⣀⠤⠒⠉⠀⠀⠀⢀⡠⠟⠉⠀⠀⠀
                                                                                                ⠀⠀⠀⠀⡸⠁⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⣀⠠⠐⠊⠁⠀⠀⠀⠀⠀⠀
                                                                                                ⠀⠀⠀⢀⢃⣖⢢⠀⠀⠀⠀⠀⣠⢤⣄⠀⠈⡄⠀⠀⣀⠠⠄⠀⠒⠒⠀⠇
                                                                                                ⠀⠀⠀⡜⠈⠛⠛⠀⣐⠂⠀⠀⠻⠿⠏⠀⠀⡗⠊⠁⠀⠀⠀⠀⠀⠀⡜⠀
                                                                                                ⠀⠀⢰⠉⢱⠀⠱⠞⠁⠉⠒⡖⠀⢀⠔⠢⡄⡇⠀⠀⠀⠀⠀⠀⠀⡐⠀⠀
                                                                                                ⠀⠀⠀⢶⠊⠀⠀⢣⠀⠀⢠⠃⠀⠘⢄⣀⢾⠃⠀⡤⠤⠤⠤⠤⠔⠀⠀⠀
                                                                                                ⠀⠀⠀⠀⢱⢄⠀⠀⠢⠔⠃⠀⠀⠀⠀⢀⢎⢢⠀⠰⡀⠀⠀⠀⠀⠀⠀⠀
                                                                                                ⠀⠀⠀⠀⣌⠀⠁⠂⠀⠀⠀⠀⠀⠐⠈⠁⢸⡤⠓⢀⡇⠀⠀⠀⠀⠀⠀⠀
                                                                                                ⣄⡀⠀⣰⢸⠀⠀⠀⠀⢀⢀⠂⠀⠀⠀⠀⠄⢳⡈⢁⡀⠀⠀⠀⠀⠀⠀⠀
                                                                                                ⢿⣷⠁⠀⠈⡄⠀⠀⠀⠈⡞⠀⠀⠀⠀⡰⠉⠀⢈⠻⠿⠀⠀⠀⠀⠀⠀⠀
                                                                                                ⡇⠈⡆⠀⠀⠱⡀⠀⠀⠀⡇⠀⠀⠀⢠⠁⠀⠀⠈⢀⠇⠀⠀⠀⠀⠀⠀⠀
                                                                                                ⠘⡄⢀⠀⠀⠀⠱⡀⠀⠀⠁⠀⠀⡠⠁⠀⠀⢰⠀⡜⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                                ⠀⠈⠉⠉⠉⠀⠐⠛⠶⠒⠣⠦⠤⠗⠒⠒⠒⠚⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀
	)";
	Controller::GoToXY(0, 21);
	cout << R"(
                              ⠸⣷⣦⠤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⠀⠀⠀
                              ⠀⠙⣿⡄⠈⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠔⠊⠉⣿⡿⠁⠀⠀⠀
                              ⠀⠀⠈⠣⡀⠀⠀⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠊⠁⠀⠀⣰⠟⠀⠀⠀⣀⣀
                              ⠀⠀⠀⠀⠈⠢⣄⠀⡈⠒⠊⠉⠁⠀⠈⠉⠑⠚⠀⠀⣀⠔⢊⣠⠤⠒⠊⠉⠀⡜
                              ⠀⠀⠀⠀⠀⠀⠀⡽⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠩⡔⠊⠁⠀⠀⠀⠀⠀⠀⠇
                              ⠀⠀⠀⠀⠀⠀⠀⡇⢠⡤⢄⠀⠀⠀⠀⠀⡠⢤⣄⠀⡇⠀⠀⠀⠀⠀⠀⠀⢰⠀
                              ⠀⠀⠀⠀⠀⠀⢀⠇⠹⠿⠟⠀⠀⠤⠀⠀⠻⠿⠟⠀⣇⠀⠀⡀⠠⠄⠒⠊⠁⠀
                              ⠀⠀⠀⠀⠀⠀⢸⣿⣿⡆⠀⠰⠤⠖⠦⠴⠀⢀⣶⣿⣿⠀⠙⢄⠀⠀⠀⠀⠀⠀
                              ⠀⠀⠀⠀⠀⠀⠀⢻⣿⠃⠀⠀⠀⠀⠀⠀⠀⠈⠿⡿⠛⢄⠀⠀⠱⣄⠀⠀⠀⠀
                              ⠀⠀⠀⠀⠀⠀⠀⢸⠈⠓⠦⠀⣀⣀⣀⠀⡠⠴⠊⠹⡞⣁⠤⠒⠉⠀⠀⠀⠀⠀
                              ⠀⠀⠀⠀⠀⠀⣠⠃⠀⠀⠀⠀⡌⠉⠉⡤⠀⠀⠀⠀⢻⠿⠆⠀⠀⠀⠀⠀⠀⠀
                              ⠀⠀⠀⠀⠀⠰⠁⡀⠀⠀⠀⠀⢸⠀⢰⠃⠀⠀⠀⢠⠀⢣⠀⠀⠀⠀⠀⠀⠀⠀
                              ⠀⠀⠀⢶⣗⠧⡀⢳⠀⠀⠀⠀⢸⣀⣸⠀⠀⠀⢀⡜⠀⣸⢤⣶⠀⠀⠀⠀⠀⠀
                              ⠀⠀⠀⠈⠻⣿⣦⣈⣧⡀⠀⠀⢸⣿⣿⠀⠀⢀⣼⡀⣨⣿⡿⠁⠀⠀⠀⠀⠀⠀
                              ⠀⠀⠀⠀⠀⠈⠻⠿⠿⠓⠄⠤⠘⠉⠙⠤⢀⠾⠿⣿⠟⠋
	)";
	Controller::GoToXY(60, 17);
	Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_BLUE);
	cout << "Nguyễn Ngọc Cảnh - Lê Hồng Ngọc";
	SetConsoleOutputCP(437);
	Controller::GoToXY(68, 19);
	cout << "23127161 - 23127236";
}

void Menu::PrintOptionsBoard(const string options[])
{
	int left = 70;
	int top = 25;
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	Controller::GoToXY(left, top);
	putchar(201);
	for (int i = 1; i < 14; i++)
		putchar(205);
	putchar(187);
	for (int i = 1; i < 4 * 2; i++)
	{
		if (i % 2 != 0)
		{
			Controller::GoToXY(68, 25 + i);
			cout << "  ";
			Controller::GoToXY(left, top + i);
			putchar(186);
			if ((i / 2) == currentOption)
			{
				Controller::SetConsoleColor(BRIGHT_WHITE, RED);
				int space = (13 - options[i / 2].length()) / 2;
				cout << string(space, ' ') << options[i / 2] << string(space, ' ');
				Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
			}
			else
			{
				int space = (13 - options[i / 2].length()) / 2;
				cout << string(space, ' ') << options[i / 2] << string(space, ' ');
			}
			Controller::GoToXY(left + 14, top + i);
			putchar(186);
			Controller::GoToXY(85, 25 + i);
			cout << "  ";
		}
		else
		{
			Controller::GoToXY(left, top + i);
			putchar(199);
			for (int j = 1; j < 14; j++)
				putchar(196);
			putchar(182);
		}
	}
	Controller::GoToXY(left, top + 4 * 2);
	putchar(200);
	for (int i = 1; i < 14; i++)
		putchar(205);
	putchar(188);
	int arrowLeft = 68;
	int arrowTop = 25 + currentOption * 2 + 1;
	Controller::GoToXY(arrowLeft, arrowTop);
	cout << "=>";
	Controller::GoToXY(left + 15, arrowTop);
	cout << "<=";
	Controller::ShowCursor(0);
}

void Menu::PlayMenu()
{
	PrintOptionsBoard(PlayOptions);
	while (true)
	{
		// xử lý sự kiện nhấn phím
		int key = _getch();
		if (key == KEY_UP || key == KEY_LEFT || key == KEY_W || key == KEY_A)
		{
			currentOption = (currentOption + 3) % 4;
			PrintOptionsBoard(PlayOptions);
		}
		else if (key == KEY_DOWN || key == KEY_RIGHT || key == KEY_S || key == KEY_D)
		{
			currentOption = (currentOption + 1) % 4;
			PrintOptionsBoard(PlayOptions);
		}
		else if (key == KEY_ENTER)
			switch (currentOption)
			{
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

void Menu::PrintRectangle(int left, int top, int width, int height)
{
	Controller::GoToXY(left, top);
	putchar(218);
	for (int i = 0; i < width; i++)
		putchar(196);
	putchar(191);

	int i = 0;
	for (; i < height; i++)
	{
		Controller::GoToXY(left, top + i + 1);
		putchar(179);
		Controller::GoToXY(left + width + 1, top + i + 1);
		putchar(179);
	}

	Controller::GoToXY(left, top + i);
	putchar(192);
	for (i = 0; i < width; i++)
		putchar(196);
	putchar(217);
}

void Menu::HighScores()
{
	currentOption = 0;
	system("cls");
	Player p[100];
	Controller::SetConsoleColor(BRIGHT_WHITE, PURPLE);
	cout << R"(
				 _   _ ___ ____ _   _   ____   ____ ___  ____  _____ ____  
				| | | |_ _/ ___| | | | / ___| / ___/ _ \|  _ \| ____/ ___| 
				| |_| || | |  _| |_| | \___ \| |  | | | | |_) |  _| \___ \ 
				|  _  || | |_| |  _  |  ___) | |__| |_| |  _ <| |___ ___) |
				|_| |_|___\____|_| |_| |____/ \____\___/|_| \_\_____|____/ 

	)";
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);

	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	PrintRectangle(30, 8, 56, 17);

	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::GoToXY(33, 9);
	cout << "No.";
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::GoToXY(38, 8 + i);
		putchar(179);
	}
	for (int i = 31; i < 38; i++)
	{
		Controller::GoToXY(i, 10);
		putchar(196);
	}
	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::GoToXY(43, 9);
	cout << "Name";
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::GoToXY(55, 8 + i);
		putchar(179);
	}
	for (int i = 39; i < 55; i++)
	{
		Controller::GoToXY(i, 10);
		putchar(196);
	}
	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::GoToXY(61, 9);
	cout << "Mode";
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::GoToXY(70, 8 + i);
		putchar(179);
	}
	for (int i = 56; i < 70; i++)
	{
		Controller::GoToXY(i, 10);
		putchar(196);
	}
	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::GoToXY(77, 9);
	cout << "Score";
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::GoToXY(87, 8 + i);
		putchar(179);
	}
	for (int i = 71; i < 87; i++)
	{
		Controller::GoToXY(i, 10);
		putchar(196);
	}
	int y = 11;
	int lines = 8;
	int n = 0;
	ifstream fin("HighScores.txt");
	while (!fin.eof())
	{
		getline(fin, p[n].playerName, ',');
		getline(fin, p[n].mode, ',');
		fin >> p[n].score;
		fin.ignore();
		n++;
	}
	fin.close();
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (p[j].score > p[i].score)
				swap(p[i], p[j]);
	for (int i = 1; i < lines; i++)
	{
		Controller::GoToXY(34, y);
		cout << i;
		Controller::GoToXY(41, y);
		cout << p[i - 1].playerName;
		Controller::GoToXY(58, y);
		cout << p[i - 1].mode;
		Controller::GoToXY(75, y);
		cout << p[i - 1].score;
		y += 2;
	}
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	PrintRectangle(55, 27, 8, 2);
	Controller::SetConsoleColor(BRIGHT_WHITE, RED);
	Controller::GoToXY(53, 28);
	putchar(175);
	Controller::GoToXY(58, 28);
	cout << "Back";
	Controller::GoToXY(66, 28);
	putchar(174);
	// while (Controller::GetConsoleInput() != 6)
	// {
	// 	Controller::PlaySound(ERROR_SOUND);
	// }
	while (true)
		if (_getch() == KEY_ENTER)
			return;
}

void Menu::TutorialScreen()
{
}

void Menu::ExitScreen()
{
}

void Menu::NormalMode()
{
	NAHGame::SetupGame(NORMAL);
	NAHGame::StartGame();
}
void Menu::HardMode()
{
	NAHGame::SetupGame(HARD);
	NAHGame::StartGame();
}
void Menu::DropMode()
{
}