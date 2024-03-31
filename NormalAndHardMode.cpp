#include "NormalAndHardMode.h"
#include "Menu.h"

GameBoard NAHGame::gameBoard;
InfoBoard NAHGame::infoBoard;

using namespace std;

void NAHGame::SetupGame(int MODE)
{
    // Hỏi thăm tên người chơi
    Controller::SetConsoleColor(BRIGHT_WHITE, YELLOW);
    system("cls");
    Controller::GoToXY(0, 0);
    Menu::PrintLogo();
    Controller::ShowCursor(true);
    Controller::SetConsoleColor(BRIGHT_WHITE, RED);
    Controller::GoToXY(35, 17);
    cout << "Please enter your name shortly, under 10 characters!";
    Controller::SetConsoleColor(BRIGHT_WHITE, LIGHT_BLUE);
    Controller::GoToXY(50, 19);
    cout << "Enter your name:  ";
    char tempName[11];
    cin.getline(tempName, 10);
    infoBoard.playerName = tempName;
    Controller::ShowCursor(false);

    // Cài đặt kích thước, vị trí của bảng và đọc file background tùy theo MODE
    ifstream f;
    char temp;
    switch (MODE)
    {
    case NORMAL:
        gameBoard.size = 4;
        gameBoard.left = 22;
        gameBoard.top = 6;
        infoBoard.mode = "NORMAL";

        f.open("Normal.txt");
        gameBoard.background = new char*[17];
        for (int i = 0; i < 17; i++) {
            gameBoard.background[i] = new char[33];
            for (int j = 0; j < 33; j++)
                f.get(gameBoard.background[i][j]);
            f.get(temp);         // lấy dấu xuống dòng vào temp
        }
        break;
    case HARD:
        gameBoard.size = 8;
        gameBoard.left = 8;
        gameBoard.top = 4;
        infoBoard.mode = "HARD";

        f.open("Hard.txt");
        gameBoard.background = new char*[33];
        for (int i = 0; i < 33; i++) {
            gameBoard.background[i] = new char[65];
            for (int j = 0; j < 65; j++)
                f.get(gameBoard.background[i][j]);
            f.get(temp);         // lấy dấu xuống dòng vào temp
        }
        break;
    }
    f.close();
    gameBoard.remainCells = gameBoard.size * gameBoard.size;

    // Sinh ngẫu nhiên các cặp "Pokemon" lên bảng
    srand(time(0));
    vector<char> pokemonsList;
    for (int i = gameBoard.remainCells / 2; i > 0; i--)
    {
        char pokemon = rand() % 26 + 'A';
        pokemonsList.push_back(pokemon);
        pokemonsList.push_back(pokemon);
    }
    random_shuffle(pokemonsList.begin(), pokemonsList.end());

    gameBoard.pokemonsBoard = new char *[gameBoard.size];
    for (int i = 0; i < gameBoard.size; i++)
    {
        gameBoard.pokemonsBoard[i] = new char[gameBoard.size];
        for (int j = 0; j < gameBoard.size; j++)
            gameBoard.pokemonsBoard[i][j] = pokemonsList[i * gameBoard.size + j];
    }
}

void NAHGame::StartGame()
{
    system("cls");
    gameBoard.Render();
    infoBoard.Render();
    while (infoBoard.lives)
    {
        if (gameBoard.chosenCell1.first != -1)
            gameBoard.RenderCell(gameBoard.chosenCell1, GREEN);
        // xử lý sự kiện nhấn phím
        int key = _getch();
        if (key == KEY_UP || key == KEY_W)
        {
            gameBoard.RenderCell(gameBoard.currentCell, BRIGHT_WHITE);
            gameBoard.currentCell.second = (gameBoard.currentCell.second + gameBoard.size - 1) % gameBoard.size;
            gameBoard.RenderCell(gameBoard.currentCell, WHITE);
        }
        else if (key == KEY_DOWN || key == KEY_S)
        {
            gameBoard.RenderCell(gameBoard.currentCell, BRIGHT_WHITE);
            gameBoard.currentCell.second = (gameBoard.currentCell.second + 1) % gameBoard.size;
            gameBoard.RenderCell(gameBoard.currentCell, WHITE);
        }

        else if (key == KEY_LEFT || key == KEY_A)
        {
            gameBoard.RenderCell(gameBoard.currentCell, BRIGHT_WHITE);
            gameBoard.currentCell.first = (gameBoard.currentCell.first + gameBoard.size - 1) % gameBoard.size;
            gameBoard.RenderCell(gameBoard.currentCell, WHITE);
        }
        else if (key == KEY_RIGHT || key == KEY_D)
        {
            gameBoard.RenderCell(gameBoard.currentCell, BRIGHT_WHITE);
            gameBoard.currentCell.first = (gameBoard.currentCell.first + 1) % gameBoard.size;
            gameBoard.RenderCell(gameBoard.currentCell, WHITE);
        }
        else if (key == KEY_ESC)
        {
            ExitScreen();
        }

        else if (key == KEY_ENTER && gameBoard.pokemonsBoard[gameBoard.currentCell.second][gameBoard.currentCell.first])
        {
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
                    for (pair<int, int> i: check) {
                        gameBoard.RenderCell(i, LIGHT_GREEN);
                        Sleep(100);
                    }
                    Sleep(400);
                    for (pair<int, int> i: check)
                        gameBoard.RenderCell(i, BRIGHT_WHITE);
                    Sleep(500);
                    for (pair<int, int> i: check)
                        gameBoard.RenderCell(i, LIGHT_GREEN);
                    Sleep(500);
                    gameBoard.RemoveCell(gameBoard.chosenCell1);
                    gameBoard.RemoveCell(gameBoard.chosenCell2);
                    for (pair<int, int> i: check)
                        gameBoard.RenderCell(i, BRIGHT_WHITE);

                    gameBoard.RenderCell(gameBoard.chosenCell2, WHITE);
                 
                    gameBoard.chosenCell1 = {-1, -1};
                    gameBoard.chosenCell2 = {-1, -1};
                    gameBoard.remainCells -= 2;
                    infoBoard.score += 10;
                    if (gameBoard.remainCells == 0) {
                        Sleep(3000);
                        WinningScreen();
                    }
                    // phát âm thanh
                }
                else
                {
                    // phát âm thanh
                    gameBoard.RenderCell(gameBoard.chosenCell1, LIGHT_RED);
                    gameBoard.RenderCell(gameBoard.chosenCell2, LIGHT_RED);
                    Sleep(500);
                    gameBoard.RenderCell(gameBoard.chosenCell1, BRIGHT_WHITE);
                    gameBoard.RenderCell(gameBoard.chosenCell2, WHITE);
                    gameBoard.chosenCell1 = {-1, -1};
                    gameBoard.chosenCell2 = {-1, -1};
                    infoBoard.lives--;
                    Controller::GoToXY(infoBoard.lives * 4 + 103, 27);
                    Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
                    cout << "  ";
                }
            }
        }
    }
    LosingScreen();
}

GameBoard::~GameBoard()
{
    for (int i = 0; i < size; i++)
        delete[] pokemonsBoard[i];
    delete[] pokemonsBoard;
    pokemonsBoard = NULL;

    for (int i = 0; i < (17 + 16*(size == 8)); i++)
        delete[] background[i];
    delete[] background;
    background = NULL;
}

void GameBoard::Render()
{
    // ReadImage();
    system("cls");
    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    Controller::GoToXY(left + 1, top);
    putchar(201);
    for (int i = 1; i < size * 8; i++)
    {
        Sleep(5);
        putchar(205);
    }
    putchar(187);
    for (int i = 1; i < size * 4; i++)
    {
        Sleep(10);
        Controller::GoToXY(size * 8 + left + 1, i + top);
        putchar(186);
    }
    Controller::GoToXY(size * 8 + left + 1, size * 4 + top);
    putchar(188);
    for (int i = 1; i < size * 8; i++)
    {
        Controller::GoToXY(size * 8 + left - i + 1, size * 4 + top);
        Sleep(5);
        putchar(205);
    }
    Controller::GoToXY(left + 1, size * 4 + top);
    putchar(200);
    for (int i = 1; i < size * 4; i++)
    {
        Sleep(10);
        Controller::GoToXY(left + 1, size * 4 + top - i);
        putchar(186);
    }
    for (int i = 1; i < size * 4; i++)
    {
        for (int j = 8; j < size * 8; j += 8)
        {
            if (i % 4 != 0)
            {
                Controller::GoToXY(j + left + 1, i + top);
                putchar(179);
            }
        }
        Sleep(10);
    }
    for (int i = 1; i < size * 8; i++)
    {
        for (int j = 4; j < size * 4; j += 4)
        {
            Controller::GoToXY(i + left + 1, j + top);
            if (i % 8 != 0)
                putchar(196);
        }
        Sleep(5);
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            RenderCell(pair<int, int>({i, j}), BRIGHT_WHITE);

    Controller::GoToXY(left + 2, top + 1);
    Controller::SetConsoleColor(WHITE, BLACK);
    cout << "       ";
    Controller::GoToXY(left + 2, top + 2);
    cout << "   " << pokemonsBoard[currentCell.second][currentCell.first] << "   ";
    Controller::GoToXY(left + 2, top + 3);
    cout << "       ";
}

void GameBoard::RenderCell(pair<int, int> cell, int color)
{
    char pokemon;
    if (cell.first == -1 || cell.second == -1 || cell.first == size || cell.second == size)
        pokemon = ' ';
    else
        pokemon = pokemonsBoard[cell.second][cell.first];
    Controller::SetConsoleColor(color, BLACK);
    if (pokemon != '\0') {
        Controller::GoToXY(left + 2 + cell.first * 8, top + 1 + cell.second * 4);
        cout << "       ";
        Controller::GoToXY(left + 2 + cell.first * 8, top + 2 + cell.second * 4);
        cout << "   " << pokemon << "   ";
        Controller::GoToXY(left + 2 + cell.first * 8, top + 3 + cell.second * 4);
        cout << "       ";
    }
    else {
        for (int i = 0; i < 3; i++) {
            Controller::GoToXY(left + 2 + cell.first * 8, top + 1 + i + cell.second * 4);
            for (int j = 0; j < 7; j++)
                cout << background[1 + cell.second * 4 + i][1 + cell.first * 8 + j];
        }
    }
}

void InfoBoard::Render()
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
    cout << "Moves:";
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
    Menu::PrintRectangle(91, 33, 14, 2);
    Menu::PrintRectangle(110, 33, 14, 2);

    Controller::SetConsoleColor(BRIGHT_WHITE, PURPLE);
    Controller::GoToXY(99, 31);
    cout << "M : Move suggestion";
    Controller::SetConsoleColor(BRIGHT_WHITE, GREEN);
    Controller::GoToXY(95, 34);
    cout << "H : Help";
    Controller::SetConsoleColor(BRIGHT_WHITE, YELLOW);
    Controller::GoToXY(113, 34);
    cout << "Esc : Exit";
}

//
bool NAHGame::ExistsLine(pair<int, int> cell1, pair<int, int> cell2) {
    pair<int, int> curr = cell1;
    if (cell1.first == cell2.first) {
        int vDirec = (cell1.second < cell2.second) ? 1 : -1;
        while (curr.second + vDirec != cell2.second) {
            curr.second += vDirec;
            if (curr.first > -1 && curr.first < gameBoard.size && curr.second > -1 && curr.second < gameBoard.size
                                                               && gameBoard.pokemonsBoard[curr.second][curr.first] != '\0')
                return false;
        }
        return true;
    }
    if (cell1.second == cell2.second) {
        int hDirec = (cell1.first < cell2.first) ? 1 : -1;
        while (curr.first + hDirec != cell2.first) {
            curr.first += hDirec;
            if (curr.first > -1 && curr.first < gameBoard.size && curr.second > -1 && curr.second < gameBoard.size
                                                               && gameBoard.pokemonsBoard[curr.second][curr.first] != '\0')
                return false;
        }
        return true;
    }
    return false;
}
vector<pair<int, int>> NAHGame::Path(vector<pair<int, int>> v) {
    int s = v.size();
    pair<int, int> curr = v[0];
    vector<pair<int, int>> path = {curr};
    for (int i = 1; i < s; i++) {
        if (curr.first == v[i].first) {
            int vDirec = (curr.second < v[i].second) ? 1 : -1;
            while (curr.second != v[i].second) {
                curr.second += vDirec;
                path.push_back(curr);
            }
        }
        else if (curr.second == v[i].second) {
            int hDirec = (curr.first < v[i].first) ? 1 : -1;
            while (curr.first != v[i].first) {
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

    if (cell1.first != cell2.first && cell1.second != cell2.second) {
    // Chỉ cần kiểm tra đường L và Z nếu hai ô không nằm trên một đường thẳng
        // Ưu tiên 2: kiểm tra đường L
        if (gameBoard.pokemonsBoard[temp1.second][temp1.first] == '\0' && ExistsLine(cell1, temp1) && ExistsLine(temp1, cell2))
            return Path(vector<pair<int, int>>({cell1, temp1, cell2}));
        if (gameBoard.pokemonsBoard[temp2.second][temp2.first] == '\0' && ExistsLine(cell1, temp2) && ExistsLine(temp2, cell2))
            return Path(vector<pair<int, int>>({cell1, temp2, cell2}));

        // Ưu tiên 2: kiểm tra đường Z
        // Z ngang (chữ N)
        temp1 = cell1;
        while (temp2.second + vDirec != cell2.second) {
            temp1.second += vDirec;
            temp2.second += vDirec;
            if (gameBoard.pokemonsBoard[temp1.second][temp1.first] == '\0' && gameBoard.pokemonsBoard[temp2.second][temp2.first] == '\0'
                && ExistsLine(temp1, temp2) && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2))
                return Path(vector<pair<int, int>>({cell1, temp1, temp2, cell2}));
        }
        // Z dọc (chữ Z)
        temp1 = cell1;
        temp2 = {cell1.first, cell2.second};
        while (temp2.first + hDirec != cell2.first) {
            temp1.first += hDirec;
            temp2.first += hDirec;
            if (gameBoard.pokemonsBoard[temp1.second][temp1.first] == '\0' && gameBoard.pokemonsBoard[temp2.second][temp2.first] == '\0'
                && ExistsLine(temp1, temp2) && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2))
                return Path(vector<pair<int, int>>({cell1, temp1, temp2, cell2}));
        }
    }

    // Ưu tiên 3: Kiểm tra đường U
    if (cell1.first != cell2.first) {
    // Chỉ cần kiểm tra U dọc nếu hai ô không cùng cột
        // U dọc (chữ U bình thường)
        temp1 = {cell1.first, cell1.second - vDirec};
        temp2 = {cell2.first, cell1.second - vDirec};
        while (temp1.second > -2 && temp1.second < gameBoard.size + 1) {
            if ((temp1.second == -1 || temp1.second == gameBoard.size
                || gameBoard.pokemonsBoard[temp1.second][temp1.first] == '\0' && gameBoard.pokemonsBoard[temp2.second][temp2.first] == '\0')
                && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2)) {
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
        while (temp1.second > -2 && temp1.second < gameBoard.size + 1) {
            if ((temp1.second == -1 || temp1.second == gameBoard.size
                || gameBoard.pokemonsBoard[temp1.second][temp1.first] == '\0' && gameBoard.pokemonsBoard[temp2.second][temp2.first] == '\0')
                && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2)) {
                if (ExistsLine(temp1, temp2))
                    return Path(vector<pair<int, int>>({cell1, temp1, temp2, cell2}));
            }
            else
                break;
            temp1.second += vDirec;
            temp2.second += vDirec;
        }
    }
    
    if (cell1.second != cell2.second) {
    // Chỉ cần kiểm tra U ngang nếu hai ô không cùng dòng
        // U ngang (chữ U nằm ngang)
        temp1 = {cell1.first - hDirec, cell1.second};
        temp2 = {cell1.first - hDirec, cell2.second};
        while (temp1.first > -2 && temp1.first < gameBoard.size + 1) {
            if ((temp1.first == -1 || temp1.first == gameBoard.size
                || gameBoard.pokemonsBoard[temp1.second][temp1.first] == '\0' && gameBoard.pokemonsBoard[temp2.second][temp2.first] == '\0')
                && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2)) {
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
        while (temp1.first > -2 && temp1.first < gameBoard.size + 1) {
            if ((temp1.first == -1 || temp1.first == gameBoard.size
                || gameBoard.pokemonsBoard[temp1.second][temp1.first] == '\0' && gameBoard.pokemonsBoard[temp2.second][temp2.first] == '\0')
                && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2)) {
                if (ExistsLine(temp1, temp2))
                    return Path(vector<pair<int, int>>({cell1, temp1, temp2, cell2}));
            }
            else
                break;
            temp1.first -= hDirec;
            temp2.first -= hDirec;
        }
    }
    return vector<pair<int, int>>({});
}

void GameBoard::RemoveCell(pair<int, int> cell)
{
    pokemonsBoard[cell.second][cell.first] = '\0';
    bool t = false, b = false, l = false, r = false;
    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);

    if (cell.second > 0 && pokemonsBoard[cell.second - 1][cell.first] == '\0') {
        for (int i = 0; i < 7; i++) {
            Controller::GoToXY(left + 2 + i + cell.first * 8, top + cell.second * 4);
            cout << background[cell.second * 4][1 + cell.first * 8 + i];
        }
        t = true;
    }
    if (cell.second < size - 1 && pokemonsBoard[cell.second + 1][cell.first] == '\0') {
        for (int i = 0; i < 7; i++) {
            Controller::GoToXY(left + 2 + i + cell.first * 8, top + cell.second * 4 + 4);
            cout << background[4 + cell.second * 4][1 + cell.first * 8 + i];
        }
        b = true;
    }
    if (cell.first > 0 && pokemonsBoard[cell.second][cell.first - 1] == '\0') {
        for (int i = 0; i < 3; i++) {
            Controller::GoToXY(left + 1 + cell.first * 8, top + 1 + i + cell.second * 4);
            cout << background[1 + cell.second * 4 + i][cell.first * 8];
        }
        l = true;
    }
    if (cell.first < size - 1 && pokemonsBoard[cell.second][cell.first + 1] == '\0') {
        for (int i = 0; i < 3; i++) {
            Controller::GoToXY(left + 9 + cell.first * 8, top + 1 + i + cell.second * 4);
            cout << background[1 + cell.second * 4 + i][cell.first * 8 + 8];
        }
        r = true;
    }

    if (t && l && pokemonsBoard[cell.second - 1][cell.first - 1] == '\0') {
        Controller::GoToXY(left + 1 + cell.first * 8, top + cell.second * 4);
        cout << background[cell.second * 4][cell.first * 8];
    }
    if (t && r && pokemonsBoard[cell.second - 1][cell.first + 1] == '\0') {
        Controller::GoToXY(left + 9 + cell.first * 8, top + cell.second * 4);
        cout << background[cell.second * 4][cell.first * 8 + 8];
    }
    if (b && l && pokemonsBoard[cell.second + 1][cell.first - 1] == '\0') {
        Controller::GoToXY(left + 1 + cell.first * 8, top + 4 + cell.second * 4);
        cout << background[cell.second * 4 + 4][cell.first * 8];
    }
    if (b && r && pokemonsBoard[cell.second + 1][cell.first + 1] == '\0') {
        Controller::GoToXY(left + 9 + cell.first * 8, top + 4 + cell.second * 4);
        cout << background[cell.second * 4 + 4][cell.first * 8 + 8];
    }
}

void NAHGame::LosingScreen()
{
}
void NAHGame::WinningScreen()
{
    system("cls");
    Menu::PrintLogo();
    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    Menu::PrintRectangle(38, 7, 42, 16);
    for (int i = 0; i < 15; i++)
    {
        Controller::GoToXY(39, 8 + i);
        cout << string(42, ' ');
    }
    Menu::PrintRectangle(40, 8, 38, 5);
    Menu::PrintRectangle(40, 14, 38, 8);
    Controller::SetConsoleColor(BRIGHT_WHITE, RED);
    Controller::GoToXY(51, 9);
    cout << "GAME ANNOUCEMENT";
    Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
    Controller::GoToXY(48, 10);
    cout << "You have won the game." << endl;
    Controller::GoToXY(51, 11);
    cout << "CONGRATULATIONS!";
    Controller::GoToXY(52, 12);
    cout << "Your score: ";
    cout << infoBoard.score;
    Controller::SetConsoleColor(BRIGHT_WHITE, GREEN);
    Controller::GoToXY(43, 16);
    cout << "Do you want to play another round?" << endl;
    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    Menu::PrintRectangle(45, 18, 8, 2);
    Menu::PrintRectangle(65, 18, 8, 2);
    Controller::SetConsoleColor(BRIGHT_WHITE, GREEN);
    Controller::GoToXY(48, 19);
    cout << "Yes";
    Controller::GoToXY(69, 19);
    cout << "No";
}

void NAHGame::ExitScreen()
{
}