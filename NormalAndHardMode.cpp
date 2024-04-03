#include "NormalAndHardMode.h"

NAHGameBoard NAHGame::gameBoard;
NAHInfoBoard NAHGame::infoBoard;

using namespace std;

void NAHGame::SetupGame(int MODE)
{
    // Hỏi thăm thông tin người chơi
    Controller::SetConsoleColor(BRIGHT_WHITE, YELLOW);
    Controller::GoToXY(0, 0);
    Menu::PrintLogo();
    Controller::ShowCursor(true);
    Controller::SetConsoleColor(BRIGHT_WHITE, RED);
    Controller::GoToXY(50, 17);
    cout << "Please enter your name shortly, under 10 characters!";
    Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_BLUE);
    Controller::GoToXY(65, 19);
    cout << "Enter your name:       ";
    char tempName[11];
    Controller::GoToXY(82, 19);
    cin.getline(tempName, 10);
    PlaySound(TEXT("Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
    infoBoard.playerName = tempName;
    Controller::ShowCursor(false);

    // Cài đặt kích thước, vị trí của bảng và đọc file background tùy theo MODE
    ifstream f;
    char temp;
    switch (MODE)
    {
    case NORMAL:
        gameBoard.size = 4;
        gameBoard.left = 28;
        gameBoard.top = 12;
        infoBoard.mode = "NORMAL";

        f.open("Normal.txt");
        gameBoard.background = new char *[17];
        for (int i = 0; i < 17; i++)
        {
            gameBoard.background[i] = new char[33];
            for (int j = 0; j < 33; j++)
                f.get(gameBoard.background[i][j]);
            f.get(temp); // lấy dấu xuống dòng vào temp
        }
        break;
    case HARD:
        gameBoard.size = 8;
        gameBoard.left = 8;
        gameBoard.top = 4;
        infoBoard.mode = "HARD";

        f.open("Hard.txt");
        gameBoard.background = new char *[33];
        for (int i = 0; i < 33; i++)
        {
            gameBoard.background[i] = new char[65];
            for (int j = 0; j < 65; j++)
                f.get(gameBoard.background[i][j]);
            f.get(temp); // lấy dấu xuống dòng vào temp
        }
        break;
    }
    f.close();
    gameBoard.remainCells = gameBoard.size * gameBoard.size;

    // Sinh ngẫu nhiên các cặp "Pokemon" lên bảng
    for (int i = gameBoard.remainCells / 2; i > 0; i--)
    {
        char pokemon = rand() % 26 + 'A';
        gameBoard.pokemonsList.push_back(pokemon);
        gameBoard.pokemonsList.push_back(pokemon);
    }
    random_shuffle(gameBoard.pokemonsList.begin(), gameBoard.pokemonsList.end());

    gameBoard.pokemonsBoard = new char *[gameBoard.size];
    for (int i = 0; i < gameBoard.size; i++)
    {
        gameBoard.pokemonsBoard[i] = new char[gameBoard.size];
        for (int j = 0; j < gameBoard.size; j++)
            gameBoard.pokemonsBoard[i][j] = gameBoard.pokemonsList[i * gameBoard.size + j];
    }

    // Các biến liên quan đến ván game
    infoBoard.score = 0;
    infoBoard.lives = 3;
    infoBoard.hints = 3;
    infoBoard.remainingTime = 600;
    gameBoard.currentCell = {0, 0};
    gameBoard.chosenCell1 = {-1, -1};
    gameBoard.chosenCell2 = {-1, -1};
    gameBoard.hint = FindPair();
    while (gameBoard.hint == pair<pair<int, int>, pair<int, int>>({}))
    {
        random_shuffle(gameBoard.pokemonsList.begin(), gameBoard.pokemonsList.end());
        for (int i = 0; i < gameBoard.size; i++)
            for (int j = 0; j < gameBoard.size; j++)
                gameBoard.pokemonsBoard[i][j] = gameBoard.pokemonsList[i * gameBoard.size + j];
        gameBoard.hint = FindPair();
    }
}

void NAHGame::StartGame()
{
    system("cls");
    gameBoard.Render();
    infoBoard.Render();
    int centiSec = 0;
    while (infoBoard.lives && infoBoard.remainingTime > 0)
    {
        if (gameBoard.chosenCell1.first != -1)
            gameBoard.RenderCell(gameBoard.chosenCell1, GREEN);
        Sleep(10);
        if (++centiSec == 60)
        {
            infoBoard.remainingTime--;
            Controller::GoToXY(113, 21);
            Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
            cout << '0' << infoBoard.remainingTime / 60 << ":" << string(infoBoard.remainingTime % 60 < 10, '0') << infoBoard.remainingTime % 60;
            centiSec = 0;
        }
        // Xử lý sự kiện nhấn phím
        if (kbhit())
        {
            int key = _getch();
            if (key == KEY_UP || key == KEY_W)
            {
                PlaySound(TEXT("Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                gameBoard.RenderCell(gameBoard.currentCell, BRIGHT_WHITE);
                gameBoard.currentCell.second = (gameBoard.currentCell.second + gameBoard.size - 1) % gameBoard.size;
                gameBoard.RenderCell(gameBoard.currentCell, WHITE);
            }
            else if (key == KEY_DOWN || key == KEY_S)
            {
                PlaySound(TEXT("Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                gameBoard.RenderCell(gameBoard.currentCell, BRIGHT_WHITE);
                gameBoard.currentCell.second = (gameBoard.currentCell.second + 1) % gameBoard.size;
                gameBoard.RenderCell(gameBoard.currentCell, WHITE);
            }

            else if (key == KEY_LEFT || key == KEY_A)
            {
                PlaySound(TEXT("Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                gameBoard.RenderCell(gameBoard.currentCell, BRIGHT_WHITE);
                gameBoard.currentCell.first = (gameBoard.currentCell.first + gameBoard.size - 1) % gameBoard.size;
                gameBoard.RenderCell(gameBoard.currentCell, WHITE);
            }
            else if (key == KEY_RIGHT || key == KEY_D)
            {
                PlaySound(TEXT("Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                gameBoard.RenderCell(gameBoard.currentCell, BRIGHT_WHITE);
                gameBoard.currentCell.first = (gameBoard.currentCell.first + 1) % gameBoard.size;
                gameBoard.RenderCell(gameBoard.currentCell, WHITE);
            }
            else if (key == KEY_ESC)
            {
                ExitGame();
            }
            else if (key == KEY_H && infoBoard.remainingTime > 30)
            {
                PlaySound(TEXT("Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                gameBoard.RenderCell(gameBoard.hint.first, LIGHT_PURPLE);
                gameBoard.RenderCell(gameBoard.hint.second, LIGHT_PURPLE);
                Sleep(500);
                gameBoard.RenderCell(gameBoard.hint.first, BRIGHT_WHITE);
                gameBoard.RenderCell(gameBoard.hint.second, BRIGHT_WHITE);
                gameBoard.RenderCell(gameBoard.currentCell, WHITE);
                if (gameBoard.chosenCell1.first != -1)
                    gameBoard.RenderCell(gameBoard.chosenCell1, GREEN);

                if (infoBoard.hints > 0)
                {
                    infoBoard.hints--;
                    if (infoBoard.hints > 0)
                    {
                        Controller::GoToXY(infoBoard.hints * 4 + 103, 25);
                        Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
                        cout << "   ";
                    }
                    else
                    {
                        Controller::GoToXY(104, 25);
                        Controller::SetConsoleColor(BRIGHT_WHITE, RED);
                        SetConsoleOutputCP(65001);
                        cout << "Cost 30 seconds ⏳";
                        SetConsoleOutputCP(437);
                    }
                }
                else
                    infoBoard.remainingTime -= 30;
            }

            else if (key == KEY_ENTER && gameBoard.pokemonsBoard[gameBoard.currentCell.second][gameBoard.currentCell.first])
            {
                PlaySound(TEXT("Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                if (gameBoard.chosenCell1.first == -1)
                {
                    gameBoard.chosenCell1 = gameBoard.currentCell;
                    gameBoard.RenderCell(gameBoard.chosenCell1, GREEN);
                }

                else if (gameBoard.currentCell == gameBoard.chosenCell1)
                {
                    gameBoard.RenderCell(gameBoard.chosenCell1, WHITE);
                    gameBoard.chosenCell1 = {-1, -1};
                }

                else
                {
                    gameBoard.chosenCell2 = gameBoard.currentCell;
                    vector<pair<int, int>> check = CheckMatching(gameBoard.chosenCell1, gameBoard.chosenCell2);
                    if (check != vector<pair<int, int>>({}))
                    {
                        for (pair<int, int> i : check)
                        {
                            gameBoard.RenderCell(i, LIGHT_GREEN);
                            Sleep(100);
                        }
                        PlaySound(TEXT("Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        Sleep(300);
                        for (pair<int, int> i : check)
                            gameBoard.RenderCell(i, BRIGHT_WHITE);
                        Sleep(400);
                        for (pair<int, int> i : check)
                            gameBoard.RenderCell(i, LIGHT_GREEN);
                        Sleep(400);
                        gameBoard.RemoveCell(gameBoard.chosenCell1);
                        gameBoard.RemoveCell(gameBoard.chosenCell2);
                        for (pair<int, int> i : check)
                            gameBoard.RenderCell(i, BRIGHT_WHITE);

                        gameBoard.RenderCell(gameBoard.chosenCell2, WHITE);

                        gameBoard.remainCells -= 2;
                        infoBoard.score += infoBoard.remainingTime;
                        Controller::GoToXY(97, 23);
                        Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
                        cout << "Current score: " << infoBoard.score;
                        if (gameBoard.remainCells == 0)
                        {
                            infoBoard.SaveData();
                            gameBoard.RenderCell(gameBoard.currentCell, BRIGHT_WHITE);
                            PlaySound(TEXT("Win.wav"), NULL, SND_FILENAME | SND_ASYNC);
                            Sleep(3000);
                            WinningScreen();
                            return;
                        }

                        if (gameBoard.chosenCell1 == gameBoard.hint.first || gameBoard.chosenCell1 == gameBoard.hint.second || gameBoard.chosenCell2 == gameBoard.hint.first || gameBoard.chosenCell2 == gameBoard.hint.second)
                        {
                            gameBoard.hint = FindPair();
                            if (gameBoard.hint == pair<pair<int, int>, pair<int, int>>({}))
                            {
                                Controller::GoToXY(gameBoard.left, gameBoard.top - 2);
                                Controller::SetConsoleColor(LIGHT_YELLOW, RED);
                                cout << "No more matches? Don't worry, the Pokemons will be reshuffled in a jiffy!";
                                gameBoard.pokemonsList.clear();
                                for (int i = gameBoard.remainCells / 2; i > 0; i--)
                                {
                                    char pokemon = rand() % 26 + 'A';
                                    gameBoard.pokemonsList.push_back(pokemon);
                                    gameBoard.pokemonsList.push_back(pokemon);
                                }
                            }
                            while (gameBoard.hint == pair<pair<int, int>, pair<int, int>>({}))
                            {
                                random_shuffle(gameBoard.pokemonsList.begin(), gameBoard.pokemonsList.end());
                                int k = 0;
                                for (int i = 0; i < gameBoard.size; i++)
                                    for (int j = 0; j < gameBoard.size; j++)
                                        if (gameBoard.pokemonsBoard[i][j] != '\0')
                                        {
                                            gameBoard.pokemonsBoard[i][j] = gameBoard.pokemonsList[k];
                                            gameBoard.RenderCell(pair<int, int>({j, i}), LIGHT_YELLOW);
                                            Sleep(100);
                                            gameBoard.RenderCell(pair<int, int>({j, i}), BRIGHT_WHITE);
                                            k++;
                                        }
                                gameBoard.hint = FindPair();
                                gameBoard.RenderCell(gameBoard.currentCell, WHITE);
                                Controller::GoToXY(gameBoard.left, gameBoard.top - 2);
                                Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
                                cout << "                                                                         ";
                            }
                        }

                        gameBoard.chosenCell1 = {-1, -1};
                        gameBoard.chosenCell2 = {-1, -1};
                    }
                    else
                    {
                        PlaySound(TEXT("Wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        gameBoard.RenderCell(gameBoard.chosenCell1, LIGHT_RED);
                        gameBoard.RenderCell(gameBoard.chosenCell2, LIGHT_RED);
                        Sleep(500);
                        gameBoard.RenderCell(gameBoard.chosenCell1, BRIGHT_WHITE);
                        gameBoard.RenderCell(gameBoard.chosenCell2, WHITE);
                        gameBoard.chosenCell1 = {-1, -1};
                        gameBoard.chosenCell2 = {-1, -1};
                        infoBoard.remainingTime -= 60;
                        infoBoard.lives--;
                        Controller::GoToXY(infoBoard.lives * 4 + 103, 27);
                        Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
                        cout << "   ";
                    }
                }
            }
        }
    }
    infoBoard.SaveData();
    PlaySound(TEXT("Lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(3000);
    if (infoBoard.lives == 0)
        LosingScreen("Out of life!");
    else
        LosingScreen("Out of time!");
    return;
}

NAHGameBoard::~NAHGameBoard()
{
    for (int i = 0; i < size; i++)
        delete[] pokemonsBoard[i];
    delete[] pokemonsBoard;
    pokemonsBoard = NULL;

    for (int i = 0; i < (17 + 16 * (size == 8)); i++)
        delete[] background[i];
    delete[] background;
    background = NULL;
}

void NAHGameBoard::Render()
{
    system("cls");
    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    Controller::GoToXY(left, top);
    // In cạnh trên của bảng
    putchar(201);
    for (int i = 1; i < size * 8; i++)
    {
        Sleep(5);
        putchar(205);
    }
    // In cạnh phải của bảng
    putchar(187);
    for (int i = 1; i < size * 4; i++)
    {
        Sleep(10);
        Controller::GoToXY(size * 8 + left, i + top);
        putchar(186);
    }
    // In cạnh dưới của bảng
    Controller::GoToXY(size * 8 + left, size * 4 + top);
    putchar(188);
    for (int i = 1; i < size * 8; i++)
    {
        Controller::GoToXY(size * 8 + left - i, size * 4 + top);
        Sleep(5);
        putchar(205);
    }
    // In cạnh trái của bảng
    Controller::GoToXY(left, size * 4 + top);
    putchar(200);
    for (int i = 1; i < size * 4; i++)
    {
        Sleep(10);
        Controller::GoToXY(left, size * 4 + top - i);
        putchar(186);
    }
    // In các đường kẻ dọc
    for (int i = 1; i < size * 4; i++)
    {
        for (int j = 8; j < size * 8; j += 8)
        {
            if (i % 4 != 0)
            {
                Controller::GoToXY(j + left, i + top);
                putchar(179);
            }
        }
        Sleep(10);
    }
    // In các đường kẻ ngang
    for (int i = 1; i < size * 8; i++)
    {
        for (int j = 4; j < size * 4; j += 4)
        {
            Controller::GoToXY(i + left, j + top);
            if (i % 8 != 0)
                putchar(196);
        }
        Sleep(5);
    }
    // In ra các "Pokemon"
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            RenderCell(pair<int, int>({i, j}), BRIGHT_WHITE);
    // In màu đậm cho currentCell
    RenderCell(pair<int, int>({0, 0}), WHITE);
}

void NAHGameBoard::RenderCell(pair<int, int> cell, int color)
{
    char pokemon;
    if (cell.first == -1 || cell.second == -1 || cell.first == size || cell.second == size)
        pokemon = ' ';
    else
        pokemon = pokemonsBoard[cell.second][cell.first];
    Controller::SetConsoleColor(color, BLACK);
    if (pokemon != '\0')
    {
        Controller::GoToXY(left + 1 + cell.first * 8, top + 1 + cell.second * 4);
        cout << "       ";
        Controller::GoToXY(left + 1 + cell.first * 8, top + 2 + cell.second * 4);
        cout << "   " << pokemon << "   ";
        Controller::GoToXY(left + 1 + cell.first * 8, top + 3 + cell.second * 4);
        cout << "       ";
    }
    else
    {
        if (color == WHITE)
            color = GRAY;
        else if (color == BRIGHT_WHITE)
            color = WHITE;
        Controller::SetConsoleColor(color, (size == 8) * BLUE + (size == 4) * YELLOW);
        for (int i = 0; i < 3; i++)
        {
            Controller::GoToXY(left + 1 + cell.first * 8, top + 1 + i + cell.second * 4);
            for (int j = 0; j < 7; j++)
                cout << background[1 + cell.second * 4 + i][1 + cell.first * 8 + j];
        }
    }
}

void NAHInfoBoard::Render()
{
    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    Menu::PrintRectangle(91, 8, 33, 8);
    Menu::PrintRectangle(91, 17, 33, 12);

    Menu::PrintRectangle(92, 9, 31, 2);
    Controller::SetConsoleColor(BRIGHT_WHITE, RED);
    Controller::GoToXY(100, 10);
    cout << "PLAYER'S INFORMATION";

    Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
    Controller::GoToXY(97, 12);
    if (playerName == "")
        playerName = "unknown";
    cout << "Player's name: " << playerName;

    Controller::GoToXY(97, 14);
    cout << "Mode: " << mode;

    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    Menu::PrintRectangle(92, 18, 31, 2);
    Controller::SetConsoleColor(BRIGHT_WHITE, RED);
    Controller::GoToXY(101, 19);
    cout << "GAME INFORMATION";
    Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
    Controller::GoToXY(97, 21);
    cout << "Remaining time: " << remainingTime / 60 << ":" << string(remainingTime % 60 < 10, '0') << remainingTime % 60;
    Controller::GoToXY(97, 23);
    cout << "Current score: " << score;
    Controller::GoToXY(97, 25);
    SetConsoleOutputCP(65001);
    cout << "Hints: 💡  💡  💡";
    SetConsoleOutputCP(437);
    Controller::GoToXY(97, 27);
    SetConsoleOutputCP(65001);
    cout << "Lives: ❤️  ❤️  ❤️";
    SetConsoleOutputCP(437);

    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    Menu::PrintRectangle(91, 30, 33, 2);
    Menu::PrintRectangle(91, 33, 33, 2);

    Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_PURPLE);
    Controller::GoToXY(104, 31);
    cout << "H : Hint";
    Controller::SetConsoleColor(BRIGHT_WHITE, RED);
    Controller::GoToXY(103, 34);
    cout << "Esc: Exit";
}

// 3 hàm dùng để kiểm tra hai ô được chọn có phải là một cặp nối được hay không, nếu có thì trả về đường nối đó
bool NAHGame::ExistsLine(pair<int, int> cell1, pair<int, int> cell2)
{
    pair<int, int> curr = cell1;
    if (cell1.first == cell2.first)
    {
        int vDirec = (cell1.second < cell2.second) ? 1 : -1;
        while (curr.second + vDirec != cell2.second)
        {
            curr.second += vDirec;
            if (curr.first > -1 && curr.first < gameBoard.size && curr.second > -1 && curr.second < gameBoard.size && gameBoard.pokemonsBoard[curr.second][curr.first] != '\0')
                return false;
        }
        return true;
    }
    if (cell1.second == cell2.second)
    {
        int hDirec = (cell1.first < cell2.first) ? 1 : -1;
        while (curr.first + hDirec != cell2.first)
        {
            curr.first += hDirec;
            if (curr.first > -1 && curr.first < gameBoard.size && curr.second > -1 && curr.second < gameBoard.size && gameBoard.pokemonsBoard[curr.second][curr.first] != '\0')
                return false;
        }
        return true;
    }
    return false;
}
vector<pair<int, int>> NAHGame::Path(vector<pair<int, int>> v)
{
    int s = v.size();
    pair<int, int> curr = v[0];
    vector<pair<int, int>> path = {curr};
    for (int i = 1; i < s; i++)
    {
        if (curr.first == v[i].first)
        {
            int vDirec = (curr.second < v[i].second) ? 1 : -1;
            while (curr.second != v[i].second)
            {
                curr.second += vDirec;
                path.push_back(curr);
            }
        }
        else if (curr.second == v[i].second)
        {
            int hDirec = (curr.first < v[i].first) ? 1 : -1;
            while (curr.first != v[i].first)
            {
                curr.first += hDirec;
                path.push_back(curr);
            }
        }
    }
    return path;
}
vector<pair<int, int>> NAHGame::CheckMatching(pair<int, int> cell1, pair<int, int> cell2)
{
    // So sánh hai Pokemon có giống nhau không
    if (gameBoard.pokemonsBoard[cell1.second][cell1.first] != gameBoard.pokemonsBoard[cell2.second][cell2.first])
        return vector<pair<int, int>>({});

    // Ưu tiên 1: kiểm tra đường I
    if (ExistsLine(cell1, cell2))
        return Path(vector<pair<int, int>>({cell1, cell2}));

    pair<int, int> temp1 = {cell1.first, cell2.second}, temp2 = {cell2.first, cell1.second};
    int vDirec = (cell1.second < cell2.second) ? 1 : -1;
    int hDirec = (cell1.first < cell2.first) ? 1 : -1;

    if (cell1.first != cell2.first && cell1.second != cell2.second)
    {
        // Chỉ cần kiểm tra đường L và Z nếu hai ô không nằm trên một đường thẳng
        // Ưu tiên 2: kiểm tra đường L
        if (gameBoard.pokemonsBoard[temp1.second][temp1.first] == '\0' && ExistsLine(cell1, temp1) && ExistsLine(temp1, cell2))
            return Path(vector<pair<int, int>>({cell1, temp1, cell2}));
        if (gameBoard.pokemonsBoard[temp2.second][temp2.first] == '\0' && ExistsLine(cell1, temp2) && ExistsLine(temp2, cell2))
            return Path(vector<pair<int, int>>({cell1, temp2, cell2}));

        // Ưu tiên 2: kiểm tra đường Z
        // Z ngang (chữ N)
        temp1 = cell1;
        while (temp2.second + vDirec != cell2.second)
        {
            temp1.second += vDirec;
            temp2.second += vDirec;
            if (gameBoard.pokemonsBoard[temp1.second][temp1.first] == '\0' && gameBoard.pokemonsBoard[temp2.second][temp2.first] == '\0' && ExistsLine(temp1, temp2) && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2))
                return Path(vector<pair<int, int>>({cell1, temp1, temp2, cell2}));
        }
        // Z dọc (chữ Z)
        temp1 = cell1;
        temp2 = {cell1.first, cell2.second};
        while (temp2.first + hDirec != cell2.first)
        {
            temp1.first += hDirec;
            temp2.first += hDirec;
            if (gameBoard.pokemonsBoard[temp1.second][temp1.first] == '\0' && gameBoard.pokemonsBoard[temp2.second][temp2.first] == '\0' && ExistsLine(temp1, temp2) && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2))
                return Path(vector<pair<int, int>>({cell1, temp1, temp2, cell2}));
        }
    }

    // Ưu tiên 3: Kiểm tra đường U
    if (cell1.first != cell2.first)
    {
        // Chỉ cần kiểm tra U dọc nếu hai ô không cùng cột
        // U dọc (chữ U bình thường)
        temp1 = {cell1.first, cell1.second - vDirec};
        temp2 = {cell2.first, cell1.second - vDirec};
        while (temp1.second > -2 && temp1.second < gameBoard.size + 1)
        {
            if ((temp1.second == -1 || temp1.second == gameBoard.size || (gameBoard.pokemonsBoard[temp1.second][temp1.first] == '\0' && gameBoard.pokemonsBoard[temp2.second][temp2.first] == '\0')) && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2))
            {
                if (ExistsLine(temp1, temp2))
                    return Path(vector<pair<int, int>>({cell1, temp1, temp2, cell2}));
            }
            else
                break;
            temp1.second -= vDirec;
            temp2.second -= vDirec;
        }
        temp1 = {cell1.first, cell2.second + vDirec};
        temp2 = {cell2.first, cell2.second + vDirec};
        while (temp1.second > -2 && temp1.second < gameBoard.size + 1)
        {
            if ((temp1.second == -1 || temp1.second == gameBoard.size || (gameBoard.pokemonsBoard[temp1.second][temp1.first] == '\0' && gameBoard.pokemonsBoard[temp2.second][temp2.first] == '\0')) && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2))
            {
                if (ExistsLine(temp1, temp2))
                    return Path(vector<pair<int, int>>({cell1, temp1, temp2, cell2}));
            }
            else
                break;
            temp1.second += vDirec;
            temp2.second += vDirec;
        }
    }

    if (cell1.second != cell2.second)
    {
        // Chỉ cần kiểm tra U ngang nếu hai ô không cùng dòng
        // U ngang (chữ U nằm ngang)
        temp1 = {cell1.first - hDirec, cell1.second};
        temp2 = {cell1.first - hDirec, cell2.second};
        while (temp1.first > -2 && temp1.first < gameBoard.size + 1)
        {
            if ((temp1.first == -1 || temp1.first == gameBoard.size || (gameBoard.pokemonsBoard[temp1.second][temp1.first] == '\0' && gameBoard.pokemonsBoard[temp2.second][temp2.first] == '\0')) && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2))
            {
                if (ExistsLine(temp1, temp2))
                    return Path(vector<pair<int, int>>({cell1, temp1, temp2, cell2}));
            }
            else
                break;
            temp1.first -= hDirec;
            temp2.first -= hDirec;
        }
        temp1 = {cell2.first + hDirec, cell1.second};
        temp2 = {cell2.first + hDirec, cell2.second};
        while (temp1.first > -2 && temp1.first < gameBoard.size + 1)
        {
            if ((temp1.first == -1 || temp1.first == gameBoard.size || (gameBoard.pokemonsBoard[temp1.second][temp1.first] == '\0' && gameBoard.pokemonsBoard[temp2.second][temp2.first] == '\0')) && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2))
            {
                if (ExistsLine(temp1, temp2))
                    return Path(vector<pair<int, int>>({cell1, temp1, temp2, cell2}));
            }
            else
                break;
            temp1.first += hDirec;
            temp2.first += hDirec;
        }
    }
    return vector<pair<int, int>>({});
}
pair<pair<int, int>, pair<int, int>> NAHGame::FindPair()
{
    for (int i = 0; i < gameBoard.size * gameBoard.size - 1; i++)
        if (gameBoard.pokemonsBoard[i / gameBoard.size][i % gameBoard.size] != '\0')
            for (int j = i + 1; j < gameBoard.size * gameBoard.size; j++)
                if (gameBoard.pokemonsBoard[j / gameBoard.size][j % gameBoard.size] != '\0')
                {
                    pair<int, int> hint1 = {i % gameBoard.size, i / gameBoard.size};
                    pair<int, int> hint2 = {j % gameBoard.size, j / gameBoard.size};
                    if (CheckMatching(hint1, hint2) != vector<pair<int, int>>({}))
                        return pair<pair<int, int>, pair<int, int>>({hint1, hint2});
                }
    return pair<pair<int, int>, pair<int, int>>({});
}

void NAHGameBoard::RemoveCell(pair<int, int> cell)
{
    pokemonsBoard[cell.second][cell.first] = '\0';
    // Xóa các cạnh và góc nếu các ô xung quanh đều đã bị xóa
    bool t = false, b = false, l = false, r = false; // top, bottom, left, right, dùng để đánh dấu xem các ô xung quanh ô đang xóa đã bị xóa chưa
    Controller::SetConsoleColor(WHITE, (size == 8) * BLUE + (size == 4) * YELLOW);

    if (cell.second > 0 && pokemonsBoard[cell.second - 1][cell.first] == '\0')
    {
        for (int i = 0; i < 7; i++)
        {
            Controller::GoToXY(left + 1 + i + cell.first * 8, top + cell.second * 4);
            cout << background[cell.second * 4][1 + cell.first * 8 + i];
        }
        t = true;
    }
    if (cell.second < size - 1 && pokemonsBoard[cell.second + 1][cell.first] == '\0')
    {
        for (int i = 0; i < 7; i++)
        {
            Controller::GoToXY(left + 1 + i + cell.first * 8, top + cell.second * 4 + 4);
            cout << background[4 + cell.second * 4][1 + cell.first * 8 + i];
        }
        b = true;
    }
    if (cell.first > 0 && pokemonsBoard[cell.second][cell.first - 1] == '\0')
    {
        for (int i = 0; i < 3; i++)
        {
            Controller::GoToXY(left + cell.first * 8, top + 1 + i + cell.second * 4);
            cout << background[1 + cell.second * 4 + i][cell.first * 8];
        }
        l = true;
    }
    if (cell.first < size - 1 && pokemonsBoard[cell.second][cell.first + 1] == '\0')
    {
        for (int i = 0; i < 3; i++)
        {
            Controller::GoToXY(left + 8 + cell.first * 8, top + 1 + i + cell.second * 4);
            cout << background[1 + cell.second * 4 + i][cell.first * 8 + 8];
        }
        r = true;
    }

    if (t && l && pokemonsBoard[cell.second - 1][cell.first - 1] == '\0')
    {
        Controller::GoToXY(left + cell.first * 8, top + cell.second * 4);
        cout << background[cell.second * 4][cell.first * 8];
    }
    if (t && r && pokemonsBoard[cell.second - 1][cell.first + 1] == '\0')
    {
        Controller::GoToXY(left + 8 + cell.first * 8, top + cell.second * 4);
        cout << background[cell.second * 4][cell.first * 8 + 8];
    }
    if (b && l && pokemonsBoard[cell.second + 1][cell.first - 1] == '\0')
    {
        Controller::GoToXY(left + cell.first * 8, top + 4 + cell.second * 4);
        cout << background[cell.second * 4 + 4][cell.first * 8];
    }
    if (b && r && pokemonsBoard[cell.second + 1][cell.first + 1] == '\0')
    {
        Controller::GoToXY(left + 8 + cell.first * 8, top + 4 + cell.second * 4);
        cout << background[cell.second * 4 + 4][cell.first * 8 + 8];
    }
}

void NAHInfoBoard::SaveData()
{
    fstream f("HighScores.txt", ios::app);
    f << playerName << ',' << mode << ',' << score << '\n';
    f.close();
}

void NAHGame::LosingScreen(string reason)
{
    system("cls");
    system("color F0");
    Menu::PrintLogo();
    Menu::PrintRectangle(56, 20, 42, 16);
    for (int i = 0; i < 15; i++)
    {
        Controller::GoToXY(57, 21 + i);
        cout << string(42, ' ');
    }
    Menu::PrintRectangle(58, 21, 38, 5);
    Menu::PrintRectangle(58, 27, 38, 8);
    Controller::SetConsoleColor(BRIGHT_WHITE, RED);
    Controller::GoToXY(69, 22);
    cout << "GAME ANNOUCEMENT";
    Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
    Controller::GoToXY(71, 23);
    cout << reason;
    Controller::GoToXY(66, 24);
    cout << "You have lost the game.";
    Controller::GoToXY(69, 25);
    cout << "Your score: " << infoBoard.score;
    Controller::SetConsoleColor(BRIGHT_WHITE, GREEN);
    Controller::GoToXY(61, 29);
    cout << "Do you want to play another round?" << endl;
    Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
    Menu::PrintRectangle(63, 31, 8, 2);
    Controller::GoToXY(64, 32);
    cout << "  Yes   ";
    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    Menu::PrintRectangle(83, 31, 8, 2);
    Controller::GoToXY(84, 32);
    cout << "   No   ";

    int yes = 1;
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
                Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_RED);
                Menu::PrintRectangle(83, 31, 8, 2);
                Controller::GoToXY(84, 32);
                cout << "   No   ";
            }
            else
            {
                Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
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
                for (int i = 0; i < 15; i++)
                {
                    Controller::GoToXY(57, 21 + i);
                    cout << string(42, ' ');
                }
                return;
            }
            else
            {
                Menu::GoodbyeScreen();
                FreeConsole();
                exit(0);
            }
            break;
        }
    }
}
void NAHGame::WinningScreen()
{
    system("cls");
    system("color F0");
    Menu::PrintLogo();
    Menu::PrintRectangle(56, 20, 42, 16);
    for (int i = 0; i < 15; i++)
    {
        Controller::GoToXY(57, 21 + i);
        cout << string(42, ' ');
    }
    Menu::PrintRectangle(58, 21, 38, 5);
    Menu::PrintRectangle(58, 27, 38, 8);
    Controller::SetConsoleColor(BRIGHT_WHITE, RED);
    Controller::GoToXY(69, 22);
    cout << "GAME ANNOUCEMENT";
    Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
    Controller::GoToXY(69, 23);
    cout << "CONGRATULATIONS!";
    Controller::GoToXY(66, 24);
    cout << "You have won the game.";
    Controller::GoToXY(69, 25);
    cout << "Your score: " << infoBoard.score;
    Controller::SetConsoleColor(BRIGHT_WHITE, GREEN);
    Controller::GoToXY(61, 29);
    cout << "Do you want to play another round?";
    Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
    Menu::PrintRectangle(63, 31, 8, 2);
    Controller::GoToXY(64, 32);
    cout << "  Yes   ";
    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    Menu::PrintRectangle(83, 31, 8, 2);
    Controller::GoToXY(84, 32);
    cout << "   No   ";

    int yes = 1;
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
                Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_RED);
                Menu::PrintRectangle(83, 31, 8, 2);
                Controller::GoToXY(84, 32);
                cout << "   No   ";
            }
            else
            {
                Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
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
                for (int i = 0; i < 15; i++)
                {
                    Controller::GoToXY(57, 21 + i);
                    cout << string(42, ' ');
                }
                return;
            }
            else
            {
                Menu::GoodbyeScreen();
                FreeConsole();
                exit(0);
            }
            break;
        }
    }
}

void NAHGame::ExitGame()
{
    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    for (int i = 0; i < 3; i++)
    {
        Controller::GoToXY(91, 33 + i);
        cout << string(35, ' ');
    }
    Menu::PrintRectangle(91, 33, 33, 2);
    Controller::SetConsoleColor(BRIGHT_WHITE, GREEN);
    Controller::GoToXY(98, 34);
    cout << "Do you want to exit?";
    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    Menu::PrintRectangle(93, 36, 8, 2);
    Controller::GoToXY(96, 37);
    cout << "Yes";
    Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
    Menu::PrintRectangle(114, 36, 8, 2);
    Controller::GoToXY(118, 37);
    cout << "No";

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
                Menu::PrintRectangle(93, 36, 8, 2);
                Controller::GoToXY(96, 37);
                cout << "Yes";
                Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_GREEN);
                Menu::PrintRectangle(114, 36, 8, 2);
                Controller::GoToXY(118, 37);
                cout << "No";
            }
            else
            {
                Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_RED);
                Menu::PrintRectangle(93, 36, 8, 2);
                Controller::GoToXY(96, 37);
                cout << "Yes";
                Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
                Menu::PrintRectangle(114, 36, 8, 2);
                Controller::GoToXY(118, 37);
                cout << "No";
            }
            yes = !yes;
            break;
        case KEY_ENTER:
            PlaySound(TEXT("Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
            if (yes)
            {
                infoBoard.SaveData();
                Menu::GoodbyeScreen();
                FreeConsole();
                exit(0);
            }
            else
            {
                Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
                for (int i = 0; i < 7; i++)
                {
                    Controller::GoToXY(91, 33 + i);
                    cout << string(35, ' ');
                }
                Menu::PrintRectangle(91, 33, 33, 2);
                Controller::SetConsoleColor(BRIGHT_WHITE, GREEN);
                Controller::GoToXY(103, 34);
                cout << "Esc: Exit";
                return;
            }
            break;
        }
    }
}