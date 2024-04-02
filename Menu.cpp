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
			PlaySound(TEXT("Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
			currentOption = (currentOption + 3) % 4;
			PrintOptionsBoard(MainOptions);
		}
		else if (key == KEY_DOWN || key == KEY_RIGHT || key == KEY_S || key == KEY_D)
		{
			PlaySound(TEXT("Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
			currentOption = (currentOption + 1) % 4;
			PrintOptionsBoard(MainOptions);
		}
		else if (key == KEY_ENTER)
		{
			PlaySound(TEXT("Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
			switch (currentOption)
			{
				case 0:
					PlayMenu();
					currentOption = 0;
					PrintOptionsBoard(MainOptions);
					break;
				case 1:
					HighScores();
					system("cls");
					PrintLogo();
					PrintOptionsBoard(MainOptions);
					break;
				case 2:
					TutorialScreen();
					system("cls");
					PrintLogo();
					PrintOptionsBoard(MainOptions);
					break;
				case 3:
					ExitScreen();
					PrintOptionsBoard(MainOptions);
					break;
			}
		}
		else if (key == KEY_ESC)
		{
			PlaySound(TEXT("Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
			ExitScreen();
		}
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
	// system("cls");
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
	Controller::SetConsoleColor(BRIGHT_WHITE, RED);
	Controller::GoToXY(arrowLeft, arrowTop);
	putchar(175);
	Controller::GoToXY(left + 16, arrowTop);
	putchar(174);
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
			PlaySound(TEXT("Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
			currentOption = (currentOption + 3) % 4;
			PrintOptionsBoard(PlayOptions);
		}
		else if (key == KEY_DOWN || key == KEY_RIGHT || key == KEY_S || key == KEY_D)
		{
			PlaySound(TEXT("Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
			currentOption = (currentOption + 1) % 4;
			PrintOptionsBoard(PlayOptions);
		}
		else if (key == KEY_ENTER)
		{
			PlaySound(TEXT("Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
			switch (currentOption)
				{
				case 0:
					NormalMode();
					cout << "Hello";
					PrintLogo();
					PrintOptionsBoard(PlayOptions);
					break;
				case 1:
					HardMode();
					PrintLogo();
					PrintOptionsBoard(PlayOptions);
					break;
				case 2:
					DropMode();
					PrintLogo();
					PrintOptionsBoard(PlayOptions);
					break;
				case 3:
					return;
				}
		}
		else if (key == KEY_ESC)
		{
			PlaySound(TEXT("Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
			return;
		}
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
	PrintRectangle(47, 8, 56, 17);

	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::GoToXY(50, 9);
	cout << "No.";
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::GoToXY(55, 8 + i);
		putchar(179);
	}
	for (int i = 48; i < 55; i++)
	{
		Controller::GoToXY(i, 10);
		putchar(196);
	}
	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::GoToXY(60, 9);
	cout << "Name";
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::GoToXY(72, 8 + i);
		putchar(179);
	}
	for (int i = 56; i < 72; i++)
	{
		Controller::GoToXY(i, 10);
		putchar(196);
	}
	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::GoToXY(78, 9);
	cout << "Mode";
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::GoToXY(87, 8 + i);
		putchar(179);
	}
	for (int i = 73; i < 87; i++)
	{
		Controller::GoToXY(i, 10);
		putchar(196);
	}
	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::GoToXY(94, 9);
	cout << "Score";
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::GoToXY(104, 8 + i);
		putchar(179);
	}
	for (int i = 88; i < 104; i++)
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
		fin.getline(p[n].playerName, 10, ',');
		fin.getline(p[n].mode, 7, ',');
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
		Controller::GoToXY(51, y);
		cout << i;
		Controller::GoToXY(58, y);
		cout << p[i - 1].playerName;
		Controller::GoToXY(75, y);
		cout << p[i - 1].mode;
		Controller::GoToXY(92, y);
		cout << p[i - 1].score;
		y += 2;
	}
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	PrintRectangle(72, 27, 8, 2);
	Controller::SetConsoleColor(BRIGHT_WHITE, RED);
	Controller::GoToXY(70, 28);
	putchar(175);
	Controller::GoToXY(75, 28);
	cout << "Back";
	Controller::GoToXY(83, 28);
	putchar(174);

	int key;
	while (true)
	{
		key = getch();
		if (key == KEY_ENTER || key == KEY_ESC)
		{
			PlaySound(TEXT("Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
			return;
		}
	}
}

void Menu::TutorialScreen()
{
	Controller::ShowCursor(0);
	system("cls");
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	int left = 27, top = 2, width = 96, height = 32;
	PrintRectangle(left, top, width, height);
	Controller::GoToXY(left + 1, 6);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	Controller::GoToXY(left + 1, 26);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	Controller::GoToXY(left + 1, 30);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	for (int i = 1; i < height; i++)
	{
		Controller::GoToXY(42, top + i);
		putchar(179);
	}
	Controller::GoToXY(42, 6);
	putchar(197);
	Controller::GoToXY(42, 26);
	putchar(197);
	Controller::GoToXY(42, 30);
	putchar(197);

	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::GoToXY(left + 3, top + 2);
	cout << "Moves:";
	Controller::GoToXY(left + 20, top + 1);
	putchar(249);
	cout << "Up:    W, up arrow";
	Controller::GoToXY(left + 58, top + 1);
	putchar(249);
	cout << "Down:  S, down arrow";
	Controller::GoToXY(left + 20, top + 3);
	putchar(249);
	cout << "Left:  A, left arrow";
	Controller::GoToXY(left + 58, top + 3);
	putchar(249);
	cout << "Right: D, right arrow";

	Controller::GoToXY(left + 3, top + 13);
	cout << "Rules:";
	Controller::GoToXY(left + 17, top + 5);
	putchar(249);
	cout << " The Matching Game (commonly known as the Pikachu Puzzle Game)";
	Controller::GoToXY(left + 17, top + 6);
	cout << " includes a board of multiple cells, each of which presents a figure.";
	Controller::GoToXY(left + 17, top + 8);
	putchar(249);
	cout << " The player finds and matches a pair of cells that contain the same";
	Controller::GoToXY(left + 17, top + 9);
	cout << " figure and connect each other in some particular pattern.";
	Controller::GoToXY(left + 17, top + 11);
	putchar(249);
	cout << " A legal match will make the two cells disappear. The game ends when";
	Controller::GoToXY(left + 17, top + 12);
	cout << " all matching pairs are found.";
	Controller::GoToXY(left + 17, top + 14);
	putchar(249);
	cout << "The game starts with a 10-minute countdown timer. If the game is not";
	Controller::GoToXY(left + 17, top + 15);
	cout << "completed when the 10-minute time limit is reached, the player loses.";
	Controller::GoToXY(left + 17, top + 17);
	putchar(249);
	cout << "Each player has 3 hints and 3 lives.";
	Controller::GoToXY(left + 17, top + 19);
	putchar(249);
	cout << "When using up all 3 hints provided, each subsequent hint";
	Controller::GoToXY(left + 17, top + 20);
	cout << "will deduct 30 seconds from the playing time.";
	Controller::GoToXY(left + 17, top + 22);
	putchar(249);
	cout << "Each time they select the wrong pair will lose 1 life and 60 seconds will";
	Controller::GoToXY(left + 17, top + 23);
	cout << "be deducted from the playing time. When all 3 lives are lost the game will end.";

	Controller::GoToXY(left + 3, top + 26);
	cout << "Scoring:";
	Controller::SetConsoleColor(BRIGHT_WHITE, GREEN);
	Controller::GoToXY(left + 28, top + 25);
	cout << "The score rises by the amount of game seconds left";
	// Controller::SetConsoleColor(BRIGHT_WHITE, GREEN);
	Controller::GoToXY(left + 35, top + 27);
	cout << "after each correct pair is chosen.";

	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::GoToXY(left + 3, top + 30);
	cout << "Developers:";
	SetConsoleOutputCP(65001);
	Controller::GoToXY(left + 31, top + 29);
	cout << "Dev 1: Nguyễn Ngọc Cảnh - 23127161";
	Controller::GoToXY(left + 31, top + 31);
	cout << "Dev 2: Lê Hồng Ngọc - 23127236";
	SetConsoleOutputCP(437);

	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	PrintRectangle(71, 37, 8, 2);
	Controller::SetConsoleColor(BRIGHT_WHITE, RED);
	Controller::GoToXY(69, 38);
	putchar(175);
	Controller::GoToXY(74, 38);
	cout << "Back";
	Controller::GoToXY(82, 38);
	putchar(174);

	int key;
	while (true)
	{
		key = getch();
		if (key == KEY_ENTER || key == KEY_ESC)
		{
			PlaySound(TEXT("Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
			return;
		}
	}
}

void Menu::ExitScreen()
{
	// Xóa option board
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 0; i < 9; i++)
	{
		Controller::GoToXY(70, 25 + i);
		cout << string(15, ' ');
	}
	// Vẽ bảng exit
	Menu::PrintRectangle(59, 26, 36, 8);
	for (int i = 0; i < 7; i++)
	{
		Controller::GoToXY(60, 27 + i);
		cout << string(36, ' ');
	}
	Controller::SetConsoleColor(BRIGHT_WHITE, GREEN);
	Controller::GoToXY(68, 29);
	cout << "Do you want to exit?";
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	Menu::PrintRectangle(63, 31, 8, 2);
	Controller::GoToXY(64, 32);
	cout << "  Yes   ";
	Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
	Menu::PrintRectangle(83, 31, 8, 2);
	Controller::GoToXY(84, 32);
	cout << "   No   ";

	int yes = 0;
	while (true)
	{
		int key = getch();
		switch (key)
		{
		case KEY_LEFT:
		case KEY_RIGHT:
		case KEY_UP:
		case KEY_DOWN:
		case KEY_W:
		case KEY_S:
		case KEY_A:
		case KEY_D:
			PlaySound(TEXT("Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (yes)
			{
				Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
				Menu::PrintRectangle(63, 31, 8, 2);
				Controller::GoToXY(64, 32);
				cout << "  Yes   ";
				Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
				Menu::PrintRectangle(83, 31, 8, 2);
				Controller::GoToXY(84, 32);
				cout << "   No   ";
			}
			else
			{
				Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_RED);
				Menu::PrintRectangle(63, 31, 8, 2);
				Controller::GoToXY(64, 32);
				cout << "  Yes   ";
				Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
				Menu::PrintRectangle(83, 31, 8, 2);
				Controller::GoToXY(84, 32);
				cout << "   No   ";
			}
			yes = !yes;
			break;
		case KEY_ENTER:
			PlaySound(TEXT("Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (yes)
			{
				GoodbyeScreen();
				FreeConsole();
				exit(0);
			}
			else
			{
				Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
				for (int i = 0; i < 9; i++)
				{
					Controller::GoToXY(59, 26 + i);
					cout << string(38, ' ');
				}
				return;
			}
			break;
		}
	}
}

void Menu::GoodbyeScreen()
{
	system("color F0");
	system("cls");
	Controller::GoToXY(0, 5);
	SetConsoleOutputCP(65001);
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	cout << R"(
      ____                 _ _                                                        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
     / ___| ___   ___   __| | |__  _   _  ___                                         ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    | |  _ / _ \ / _ \ / _` | '_ \| | | |/ _ \                                        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⡿⠿⠿⢿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    | |_| | (_) | (_) | (_| | |_) | |_| |  __/                                        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠞⠋⠁⠀⠀⠀⠀⡸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
     \____|\___/ \___/ \__,_|_.__/ \__, |\___|                                        ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡔⠁⠀⠀⠀⠀⠀⠀⡰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                   |___/                                              ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠞⠀⠀⠀⠀⠀⠀⠀⡴⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠎⠀⠀⠀⠀⠀⠀⡠⡞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠀⠀⠀⠀⠀⡠⢪⠎⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠁⠀⠀⠀⡠⢊⠔⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠔⠂⠀⠉⠀⠀⠀⠈⠉⠀⠒⠠⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
     ____                                  _       _                                  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠒⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    / ___|  ___  ___   _   _  ___  _   _  | | __ _| |_ ___ _ __                       ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    \___ \ / _ \/ _ \ | | | |/ _ \| | | | | |/ _` | __/ _ \ '__|                      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠃⠀⢀⣤⡤⠤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢱⠤⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
     ___) |  __/  __/ | |_| | (_) | |_| | | | (_| | ||  __/ |                         ⠀⠀⢠⠠⠶⠖⠦⢄⠀⠀⠀⢀⠏⠀⠀⣿⣿⣧⣤⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠄⠀⠉⠢⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀
    |____/ \___|\___|  \__, |\___/ \__,_| |_|\__,_|\__\___|_|                         ⠀⢸⠉⠀⠀⠀⠀⠀⠱⣄⣠⠮⠠⢤⠀⠘⠻⠿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠑⢦⡀⠀⠀⠀⠀⠀⠀
                       |___/                                                          ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢧⠀⠀⠀⢱⠀⠀⠀⠀⡀⠀⠀⠀⠘⠂⠀⠀⠀⠀⢰⣏⠉⣿⡄⠀⠀⣌⢣⠀⠀⠀⠀⠀⠙⢦⡀⠀⠀⠀⠀
                                                                                      ⠀⠀⡄⠀⠀⠀⠀⠀⠀⠀⠀⢣⠀⠀⢸⠀⠀⠀⠀⣱⣦⣤⣤⣆⠀⠀⠀⠀⠀⠸⣿⣿⣿⠇⠀⠰⠉⢧⣣⠀⠀⠀⠀⠀⠀⠱⡄⠀⠀⠀
                                                                                      ⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢧⠴⠃⠀⠀⠀⠀⣟⠛⠛⠻⢿⣿⣶⠒⠁⠀⠀⠈⠉⠁⠀⠀⡇⠀⠀⠙⢇⠀⠀⠀⠀⠀⠀⠈⢆⠀⠀
                                                                                      ⠀⠀⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢧⠀⠀⠀⠀⠀⡏⠉⠁⠒⢄⣹⠃⠀⠀⠀⡴⠊⠉⠉⠑⣤⠀⠀⠀⠀⠀⠑⢦⣤⣀⣀⣀⣀⣈⣆⠀
                                                                                      ⠀⠀⢸⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡆⠀⠀⠀⠀⡇⠀⠀⠀⡴⠁⠀⠀⠀⢸⡄⠀⠀⠠⠀⢸⠉⠉⠉⠉⠉⠉⠉⠙⠻⣿⣿⣿⣿⣿⡆
                                                                                      ⠀⠀⠀⢇⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠘⠦⠤⠊⠀⠀⠀⠀⠀⠘⣅⠀⠀⠀⣴⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠛⡿⢷
                                                                                      ⠀⠀⠀⠘⣎⢂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣈⠭⠔⠋⠒⢯⡦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠌⠀⠀
                                                                                      ⠀⠀⠀⠀⠘⡄⠣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢂⠉⠒⠂⠠⢄⠤⠀⠐⠂⠉⠉⠀⠀⠀⠀⠀⠀⠈⠛⢷⣄⠀⠀⠀⠀⠀⠀⢀⠎⠀⠀⠀
                                                                                      ⠀⠀⠀⠀⠀⠘⣄⠑⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠒⠒⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⡦⡀⠀⠀⢠⠃⠀⠀⠀⠀
                                                                                      ⠀⠀⠀⠀⠀⠀⣏⣀⠞⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢎⢑⣤⠃⠀⠀⠀⠀⠀
                                                                                      ⠀⠀⠀⠀⠀⢠⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢏⠁⠀⠀⠀⠀⠀⠀
                                                                                      ⠀⠀⠀⠀⠀⡌⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠈⠂⠄⡀⠀⠀⠀⠀⠀⠀⢀⡏⠀⠀⠀⠀⠀⠀⠀
                                                                                      ⠀⠀⠀⠀⢠⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠒⠂⠤⢬⠥⠶⠦⠤⠤⠠⠊⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                      ⠀⠀⠀⠀⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                      ⠀⠀⠀⡘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣆⡠⠚⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                      ⠀⠀⠰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                      ⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                      ⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                      ⠀⠀⠸⣕⠂⠤⠤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡀⠀⠀⠀⠀⠀⠀⢀⡠⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                      ⠀⠀⠀⢈⡢⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠁⠀⠉⢀⠜⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                      ⢀⣴⡚⠍⠐⠄⠀⠀⠀⢉⣁⠖⠀⠀⠀⠀⠀⠒⠒⠒⠢⠤⠤⣤⠤⠀⠀⠀⠰⠶⢅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                      ⢿⣝⣂⠡⠤⠜⠒⠒⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠓⠤⣀⠀⠀⢀⠔⠛⣢⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
                                                                                      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠐⠃⣤⣈⣺⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
	)";
	Sleep(3000);
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