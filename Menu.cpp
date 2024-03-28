#include "Menu.h"

int Menu::currentOption = 0;
const string Menu::MainOptions[4] = { "Play", "High Scores", "Tutorial", "Exit" };
const string Menu::PlayOptions[4] = { "Normal Mode", "Hard Mode", "Drop Mode", "Back" };

void Menu::MainScreen()
{
	DisplayMenu(MainOptions);
	while (true)
	{
		// xử lý sự kiện nhấn phím
		int key = _getch();
		if (key == KEY_UP || key == KEY_LEFT || key == KEY_W || key == KEY_A)
		{
			currentOption = (currentOption + 4) % 5;
			DisplayMenu(MainOptions);
		}
		else if (key == KEY_DOWN || key == KEY_RIGHT || key == KEY_S || key == KEY_D)
		{
			currentOption = (currentOption + 1) % 5;
			DisplayMenu(MainOptions);
		}
		else if (key == KEY_ENTER)
			switch (currentOption)
			{
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
	Controller::GoToXY(44, 0);
	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	cout << "Nguyen Ngoc Canh - Le Hong Ngoc";
	Controller::GoToXY(48, 1);
	cout << "23127161 - 23127236";
	Controller::GoToXY(38, 8);
	Controller::SetConsoleColor(BRIGHT_WHITE, GREEN);

	PrintOptionsBoard(options);
}

void Menu::PrintOptionsBoard(const string options[])
{
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	int left = 50;
	int top = 20;
	Controller::GoToXY(left, top);
	putchar(201);
	for (int i = 1; i < 14; i++)
	{
		putchar(205);
	}
	putchar(187);
	for (int i = 1; i < 4 * 2; i++)
	{
		if (i % 2 != 0)
		{
			Controller::GoToXY(left, top + i);
			putchar(186);
			if ((i / 2) == currentOption) 
			{
				Controller::SetConsoleColor(BRIGHT_WHITE, RED);
				int space = (13 - options[i / 2].length()) / 2;
				cout << string(space, ' ') << options[i / 2] << string(space, ' ');
				Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
			}
			else {
				int space = (13 - options[i / 2].length()) / 2; 
				cout << string(space, ' ') << options[i / 2] << string(space, ' ');
			}
			Controller::GoToXY(left + 14, top + i);
			putchar(186);
		}
		else
		{
			Controller::GoToXY(left, top + i);
			putchar(199);
			for (int j = 1; j < 14; j++)
			{
				putchar(196);
			}
			putchar(182);
		}
	}
	Controller::GoToXY(left, top + 4 * 2);
	putchar(200);
	for (int i = 1; i < 14; i++)
	{
		putchar(205);
	}
	putchar(188);

	int arrowLeft = 48;
	int arrowTop = 20 + currentOption * 2 + 1;
	Controller::GoToXY(arrowLeft, arrowTop);
	cout << "=>";
	Controller::GoToXY(left + 15, arrowTop);
	cout << "<=";
}

void Menu::PlayMenu()
{
	DisplayMenu(PlayOptions);
	while (true)
	{
		// xử lý sự kiện nhấn phím
		int key = _getch();
		if (key == KEY_UP || key == KEY_LEFT || key == KEY_W || key == KEY_A)
		{
			currentOption = (currentOption + 4) % 5;
			DisplayMenu(PlayOptions);
		}
		else if (key == KEY_DOWN || key == KEY_RIGHT || key == KEY_S || key == KEY_D)
		{
			currentOption = (currentOption + 1) % 5;
			DisplayMenu(PlayOptions);
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
	PrintRectangle(5, 8, 56, 17);

	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::GoToXY(8, 9);
	cout << "STT";
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::GoToXY(13, 8 + i);
		putchar(179);
	}
	for (int i = 6; i < 13; i++)
	{
		Controller::GoToXY(i, 10);
		putchar(196);
	}
	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::GoToXY(18, 9);
	cout << "Name";
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::GoToXY(30, 8 + i);
		putchar(179);
	}
	for (int i = 14; i < 30; i++)
	{
		Controller::GoToXY(i, 10);
		putchar(196);
	}
	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::GoToXY(36, 9);
	cout << "Mode";
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::GoToXY(45, 8 + i);
		putchar(179);
	}
	for (int i = 31; i < 45; i++)
	{
		Controller::GoToXY(i, 10);
		putchar(196);
	}
	Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::GoToXY(52, 9);
	cout << "Score";
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::GoToXY(62, 8 + i);
		putchar(179);
	}
	for (int i = 46; i < 62; i++)
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
		Controller::GoToXY(9, y);
		cout << i;
		Controller::GoToXY(16, y);
		cout << p[i - 1].playerName;
		Controller::GoToXY(33, y);
		cout << p[i - 1].mode;
		Controller::GoToXY(50, y);
		cout << p[i - 1].score;
		y += 2;
	}
	Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
	PrintRectangle(45, 27, 8, 2);
	Controller::SetConsoleColor(BRIGHT_WHITE, RED);
	Controller::GoToXY(43, 28);
	putchar(175);
	Controller::GoToXY(48, 28);
	cout << "Back";
	Controller::GoToXY(56, 28);
	putchar(174);
	// while (Controller::GetConsoleInput() != 6)
	// {
	// 	Controller::PlaySound(ERROR_SOUND);
	// }
}

void Menu::TutorialScreen()
{
}

void Menu::ExitScreen()
{
}

void Menu::NormalMode()
{
}
void Menu::HardMode()
{
}
void Menu::DropMode()
{
}