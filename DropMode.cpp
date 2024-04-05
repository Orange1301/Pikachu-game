#include "DropMode.h"

DGameBoard DGame::gameBoard;
DInfoBoard DGame::infoBoard;

using namespace std;

char List::GetPokemon(int n)
{
    if (n > height)
        return '\0';
    if (n == height)
        return tail->pokemon;
    Node *curr = head;
    for (int i = 0; i < n; i++)
        curr = curr->next;
    return curr->pokemon;
}

void DGame::SetupGame() // Thiết lập trò chơi
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
    PlaySound(TEXT("Sound/Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
    infoBoard.playerName = tempName;
    Controller::ShowCursor(false);

    // Cài đặt kích thước, vị trí của bảng và đọc file background
    gameBoard.left = 8;
    gameBoard.top = 4;
    infoBoard.mode = "DROP";

    ifstream f;
    char temp;
    f.open("Background/Hard.txt");
    gameBoard.background = new char *[33];
    for (int i = 0; i < 33; i++)
    {
        gameBoard.background[i] = new char[65];
        for (int j = 0; j < 65; j++)
            f.get(gameBoard.background[i][j]);
        f.get(temp); // lấy dấu xuống dòng vào temp
    }
    f.close();
    gameBoard.remainCells = 64;

    // Sinh ngẫu nhiên các cặp "Pokemon" lên bảng
    for (int i = 32; i > 0; i--)
    {
        char pokemon = rand() % 26 + 'A';
        gameBoard.pokemonsList.push_back(pokemon);
        gameBoard.pokemonsList.push_back(pokemon);
    }
    random_shuffle(gameBoard.pokemonsList.begin(), gameBoard.pokemonsList.end());

    for (int i = 0; i < 8; i++)
    {
        gameBoard.pokemonsBoard[i].height = 7;
        gameBoard.pokemonsBoard[i].head = new Node;
        gameBoard.pokemonsBoard[i].head->pokemon = gameBoard.pokemonsList[i * 8];
        gameBoard.pokemonsBoard[i].head->prev = NULL;
        gameBoard.pokemonsBoard[i].head->next = new Node;
        Node *curr = gameBoard.pokemonsBoard[i].head->next;
        curr->prev = gameBoard.pokemonsBoard[i].head;
        for (int j = 1; j < 7; j++)
        {
            curr->pokemon = gameBoard.pokemonsList[i * 8 + j];

            curr->next = new Node;
            curr->next->prev = curr;
            curr = curr->next;
        }
        curr->pokemon = gameBoard.pokemonsList[i * 8 + 7];
        curr->next = NULL;
        gameBoard.pokemonsBoard[i].tail = curr;
    }
    // Các biến liên quan đến ván game
    infoBoard.score = 0;
    infoBoard.lives = 3;
    infoBoard.hints = 3;
    infoBoard.remainingTime = 600;
    // Các biến liên quan đến vị trí và trạng thái của các ô trong bảng Pokemon
    gameBoard.currentCell = {0, 0};
    gameBoard.chosenCell1 = {-1, -1};
    gameBoard.chosenCell2 = {-1, -1};
    gameBoard.hint = FindPair();                                       // Tìm cặp nối được
    while (gameBoard.hint == pair<pair<int, int>, pair<int, int>>({})) // Điều kiện bảo rằng trò chơi sẽ không bắt đầu nếu không có cặp Pokemon nào có thể nối được với nhau từ đầu
    {
        random_shuffle(gameBoard.pokemonsList.begin(), gameBoard.pokemonsList.end());
        for (int i = 0; i < 8; i++)
        {
            Node *curr = gameBoard.pokemonsBoard[i].head;
            for (int j = 0; j < 8; j++)
            {
                curr->pokemon = gameBoard.pokemonsList[i * 8 + j];
                curr = curr->next;
            }
        }
        gameBoard.hint = FindPair();
    }
}

void DGame::StartGame() // Hàm chính bắt đầu trò chơi
{
    system("cls");      // Xoá màn hình hiện tại
    gameBoard.Render(); // In ra bảng game Pokemon
    infoBoard.Render(); // In ra bảng thông tin người chơi
    int centiSec = 0;
    while (infoBoard.lives && infoBoard.remainingTime > 0) // Kiểm tra có còn mạng và thời gian không
    {
        if (gameBoard.chosenCell1.first != -1) // Đổi màu cho ô được chọn
            gameBoard.RenderCell(gameBoard.chosenCell1, GREEN);
        Sleep(10);
        if (++centiSec == 60) // Cập nhật thời gian của trò chơi mỗi khi trôi qua 1 giây
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
            // Di chuyển tới ô nào thì ô đó sẽ được tô màu trắng đậm hơn
            if (key == KEY_UP || key == KEY_W)
            {
                PlaySound(TEXT("Sound/Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                gameBoard.RenderCell(gameBoard.currentCell, BRIGHT_WHITE);
                gameBoard.currentCell.second = (gameBoard.currentCell.second + 8 - 1) % 8;
                gameBoard.RenderCell(gameBoard.currentCell, WHITE);
            }
            else if (key == KEY_DOWN || key == KEY_S)
            {
                PlaySound(TEXT("Sound/Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                gameBoard.RenderCell(gameBoard.currentCell, BRIGHT_WHITE);
                gameBoard.currentCell.second = (gameBoard.currentCell.second + 1) % 8;
                gameBoard.RenderCell(gameBoard.currentCell, WHITE);
            }

            else if (key == KEY_LEFT || key == KEY_A)
            {
                PlaySound(TEXT("Sound/Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                gameBoard.RenderCell(gameBoard.currentCell, BRIGHT_WHITE);
                gameBoard.currentCell.first = (gameBoard.currentCell.first + 8 - 1) % 8;
                gameBoard.RenderCell(gameBoard.currentCell, WHITE);
            }
            else if (key == KEY_RIGHT || key == KEY_D)
            {
                PlaySound(TEXT("Sound/Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                gameBoard.RenderCell(gameBoard.currentCell, BRIGHT_WHITE);
                gameBoard.currentCell.first = (gameBoard.currentCell.first + 1) % 8;
                gameBoard.RenderCell(gameBoard.currentCell, WHITE);
            }
            else if (key == KEY_ESC) // Nhấn phím ESC để thoát game
                ExitGame();
            else if (key == KEY_H && infoBoard.remainingTime > 30) // Nhấn H để hiện gợi ý 1 cặp Pokemon hợp lệ, cặp Pokemon gợi ý được tô màu tím
            {
                PlaySound(TEXT("Sound/Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                gameBoard.RenderCell(gameBoard.hint.first, LIGHT_PURPLE);
                gameBoard.RenderCell(gameBoard.hint.second, LIGHT_PURPLE);
                Sleep(500);
                gameBoard.RenderCell(gameBoard.hint.first, BRIGHT_WHITE);
                gameBoard.RenderCell(gameBoard.hint.second, BRIGHT_WHITE);
                gameBoard.RenderCell(gameBoard.currentCell, WHITE);
                if (gameBoard.chosenCell1.first != -1)
                    gameBoard.RenderCell(gameBoard.chosenCell1, GREEN);

                // Kiểm tra số lượt hint, nếu hết 3 lượt thì mỗi lần nhận gợi ý thời gian sẽ bị trừ đi 30s
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

            else if (key == KEY_ENTER && 7 - gameBoard.currentCell.second <= gameBoard.pokemonsBoard[gameBoard.currentCell.first].height)
            {
                PlaySound(TEXT("Sound/Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
                if (gameBoard.chosenCell1.first == -1) // Tô màu xanh lá cho ô được chọn
                {
                    gameBoard.chosenCell1 = gameBoard.currentCell;
                    gameBoard.RenderCell(gameBoard.chosenCell1, GREEN);
                }

                else if (gameBoard.currentCell == gameBoard.chosenCell1) // Khi nhấn 2 lần vào 1 ô thì huỷ chọn, chuyển lại thành màu trắng
                {
                    gameBoard.RenderCell(gameBoard.chosenCell1, WHITE);
                    gameBoard.chosenCell1 = {-1, -1};
                }

                else
                {
                    gameBoard.chosenCell2 = gameBoard.currentCell;
                    Controller::GoToXY(94, 37);
                    vector<pair<int, int>> check = CheckMatching(gameBoard.chosenCell1, gameBoard.chosenCell2);
                    if (check != vector<pair<int, int>>({})) // Kiểm tra nếu chọn đúng cặp Pokemon
                    {
                        for (pair<int, int> i : check)
                        {
                            gameBoard.RenderCell(i, LIGHT_GREEN);
                            Sleep(100);
                        }
                        PlaySound(TEXT("Sound/Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        Sleep(300);
                        for (pair<int, int> i : check)
                            gameBoard.RenderCell(i, BRIGHT_WHITE);
                        Sleep(400);
                        for (pair<int, int> i : check)
                            gameBoard.RenderCell(i, LIGHT_GREEN);
                        Sleep(400);
                        for (pair<int, int> i : check)
                            gameBoard.RenderCell(i, BRIGHT_WHITE);

                        // if else này để đảm bảo ô nằm cao hơn sẽ được xóa trước, phòng trường hợp hai ô nằm cùng một cột,
                        // nếu xóa ô dưới trước thì ô cần xóa phía trên đã bị thay đổi, dẫn đến xóa sai, thậm chí gây ra lỗi
                        // nếu ô được chọn phía trên là tail
                        if (gameBoard.chosenCell1.second < gameBoard.chosenCell2.second)
                        {
                            gameBoard.RemoveCell(gameBoard.chosenCell1);
                            gameBoard.RemoveCell(gameBoard.chosenCell2);
                        }
                        else
                        {
                            gameBoard.RemoveCell(gameBoard.chosenCell2);
                            gameBoard.RemoveCell(gameBoard.chosenCell1);
                        }

                        for (int i = 0; i < 8; i++)
                            gameBoard.RenderCell(pair<int, int>({gameBoard.chosenCell1.first, i}), BRIGHT_WHITE);
                        if (gameBoard.chosenCell2.first != gameBoard.chosenCell1.first)
                            for (int i = 0; i < 8; i++)
                                gameBoard.RenderCell(pair<int, int>({gameBoard.chosenCell2.first, i}), BRIGHT_WHITE);
                        gameBoard.RenderCell(gameBoard.chosenCell2, WHITE);
                        // Cập nhật điểm số
                        gameBoard.remainCells -= 2;
                        infoBoard.score += infoBoard.remainingTime;
                        Controller::GoToXY(97, 23);
                        Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
                        cout << "Current score: " << infoBoard.score;
                        if (gameBoard.remainCells == 0) // Kiểm tra nếu không còn ô nào thì chiến thắng
                        {
                            infoBoard.SaveData();
                            gameBoard.RenderCell(gameBoard.currentCell, BRIGHT_WHITE);
                            PlaySound(TEXT("Sound/Win.wav"), NULL, SND_FILENAME | SND_ASYNC);
                            Sleep(3000);
                            WinningScreen();
                            return;
                        }

                        // Kiểm tra ô đã chọn có trùng với các ô gợi ý không
                        if (gameBoard.chosenCell1.first == gameBoard.hint.first.first || gameBoard.chosenCell1.first == gameBoard.hint.second.first || gameBoard.chosenCell2.first == gameBoard.hint.first.first || gameBoard.chosenCell2.first == gameBoard.hint.second.first)
                        {
                            gameBoard.hint = FindPair();
                            if (gameBoard.hint == pair<pair<int, int>, pair<int, int>>({})) // Nếu không còn cặp Pokemon nào khớp với các ô gợi ý thì hiện thông báo và reshuffing bảng Pokemon
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
                            while (gameBoard.hint == pair<pair<int, int>, pair<int, int>>({})) // Tạo lại các cặp Pokemon mới
                            {
                                random_shuffle(gameBoard.pokemonsList.begin(), gameBoard.pokemonsList.end());
                                int k = 0;
                                for (int i = 0; i < 8; i++)
                                {
                                    Node *curr = gameBoard.pokemonsBoard[i].head;
                                    int j = 7;
                                    while (curr != NULL)
                                    {
                                        curr->pokemon = gameBoard.pokemonsList[k];
                                        curr = curr->next;
                                        gameBoard.RenderCell(pair<int, int>({i, j}), LIGHT_YELLOW);
                                        Sleep(100);
                                        gameBoard.RenderCell(pair<int, int>({i, j}), BRIGHT_WHITE);
                                        j--;
                                        k++;
                                    }
                                }
                                gameBoard.hint = FindPair(); // Tìm ô gợi ý mới
                                // Xoá dòng thông báo trên màn hình
                                gameBoard.RenderCell(gameBoard.currentCell, WHITE);
                                Controller::GoToXY(gameBoard.left, gameBoard.top - 2);
                                Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
                                cout << "                                                                         ";
                            }
                        }
                        // Reset các ô đã chọn
                        gameBoard.chosenCell1 = {-1, -1};
                        gameBoard.chosenCell2 = {-1, -1};
                    }
                    else // Nếu chọn sai cặp Pokemon, thời gian và số mạng sẽ bị giảm đi
                    {
                        PlaySound(TEXT("Sound/Wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        gameBoard.RenderCell(gameBoard.chosenCell1, LIGHT_RED);
                        gameBoard.RenderCell(gameBoard.chosenCell2, LIGHT_RED);
                        Sleep(500);
                        gameBoard.RenderCell(gameBoard.chosenCell1, BRIGHT_WHITE);
                        gameBoard.RenderCell(gameBoard.chosenCell2, WHITE);
                        gameBoard.chosenCell1 = {-1, -1};
                        gameBoard.chosenCell2 = {-1, -1};
                        infoBoard.lives--;
                        infoBoard.remainingTime -= 60;
                        Controller::GoToXY(infoBoard.lives * 4 + 103, 27);
                        Controller::SetConsoleColor(BRIGHT_WHITE, BLUE);
                        cout << "   ";
                    }
                }
            }
        }
    }
    // Kết thúc trò chơi do hết mạng hoặc hết thời gian, thông tin sẽ được lưu và hiển thị màn hình thua
    PlaySound(TEXT("Sound/Lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
    infoBoard.SaveData();
    Sleep(3000);
    if (infoBoard.lives == 0)
        LosingScreen("Out of life!");
    else
        LosingScreen("Out of time!");
    return;
}

DGameBoard::~DGameBoard()
{
    for (int i = 0; i < 8; i++)
    {
        Node *curr = pokemonsBoard[i].head;
        while (curr != NULL)
        {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
        pokemonsBoard[i].head = NULL;
    }

    for (int i = 0; i < 33; i++)
        delete[] background[i];
    delete[] background;
    background = NULL;
}

void DGameBoard::Render() // Vẽ toàn bộ bảng chơi Pokemon
{
    system("cls");
    Controller::SetConsoleColor(BRIGHT_WHITE, BLACK);
    Controller::GoToXY(left, top);
    // In cạnh trên của bảng
    putchar(201);
    for (int i = 1; i < 64; i++)
    {
        Sleep(5);
        putchar(205);
    }
    // In cạnh phải của bảng
    putchar(187);
    for (int i = 1; i < 32; i++)
    {
        Sleep(10);
        Controller::GoToXY(64 + left, i + top);
        putchar(186);
    }
    // In cạnh dưới của bảng
    Controller::GoToXY(64 + left, 32 + top);
    putchar(188);
    for (int i = 1; i < 64; i++)
    {
        Controller::GoToXY(64 + left - i, 32 + top);
        Sleep(5);
        putchar(205);
    }
    // In cạnh trái của bảng
    Controller::GoToXY(left, 32 + top);
    putchar(200);
    for (int i = 1; i < 32; i++)
    {
        Sleep(10);
        Controller::GoToXY(left, 32 + top - i);
        putchar(186);
    }
    // In các đường kẻ dọc
    for (int i = 1; i < 32; i++)
    {
        for (int j = 8; j < 64; j += 8)
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
    for (int i = 1; i < 64; i++)
    {
        for (int j = 4; j < 32; j += 4)
        {
            Controller::GoToXY(i + left, j + top);
            if (i % 8 != 0)
                putchar(196);
        }
        Sleep(5);
    }
    // In ra các "Pokemon"
    for (int i = 0; i < 8; i++)
    {
        Node *curr = pokemonsBoard[i].head;
        for (int j = 7; j > -1; j--)
        {
            Controller::GoToXY(left + 1 + i * 8, top + 1 + j * 4);
            cout << "       ";
            Controller::GoToXY(left + 1 + i * 8, top + 2 + j * 4);
            cout << "   " << curr->pokemon << "   ";
            Controller::GoToXY(left + 1 + i * 8, top + 3 + j * 4);
            cout << "       ";
            curr = curr->next;
        }
    }
    // In màu đậm cho currentCell
    Controller::SetConsoleColor(WHITE, BLACK);
    Controller::GoToXY(left + 1, top + 1);
    cout << "       ";
    Controller::GoToXY(left + 1, top + 2);
    cout << "   " << pokemonsBoard[0].tail->pokemon << "   ";
    Controller::GoToXY(left + 1, top + 3);
    cout << "       ";
}

void DGameBoard::RenderCell(pair<int, int> cell, int color) // Vẽ 1 ô trong bảng game Pokemon
{
    char pokemon;
    if (cell.first == -1 || cell.second == -1 || cell.first == 8 || cell.second == 8) // Kiểm tra có nằm ngoài biên của bảng hay không
        pokemon = ' ';
    else
        pokemon = pokemonsBoard[cell.first].GetPokemon(7 - cell.second);
    Controller::SetConsoleColor(color, BLACK);
    if (pokemon != '\0') // Kiểm tra nếu ô có chứa Pokemon
    {
        Controller::GoToXY(left + 1 + cell.first * 8, top + 1 + cell.second * 4);
        cout << "       ";
        Controller::GoToXY(left + 1 + cell.first * 8, top + 2 + cell.second * 4);
        cout << "   " << pokemon << "   ";
        Controller::GoToXY(left + 1 + cell.first * 8, top + 3 + cell.second * 4);
        cout << "       ";
    }
    else // Nếu là ô trống sẽ in ra background tại vị trí của ô đó
    {
        if (color == WHITE)
            color = GRAY;
        else if (color == BRIGHT_WHITE)
            color = WHITE;
        Controller::SetConsoleColor(color, BLUE);
        for (int i = 0; i < 3; i++)
        {
            Controller::GoToXY(left + 1 + cell.first * 8, top + 1 + i + cell.second * 4);
            for (int j = 0; j < 7; j++)
                cout << background[1 + cell.second * 4 + i][1 + cell.first * 8 + j];
        }
    }
}

void DInfoBoard::Render() // Vẽ bảng thông tin người chơi
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
bool DGame::ExistsLine(pair<int, int> cell1, pair<int, int> cell2) // Kiểm tra có đường nối nào giữa 2 ô trên bảng game Pokemon không
{
    pair<int, int> curr = cell1;
    if (cell1.first == cell2.first) // Kiểm tra 2 ô cùng hàng
    {
        int vDirec = (cell1.second < cell2.second) ? 1 : -1;
        while (curr.second + vDirec != cell2.second)
        {
            curr.second += vDirec;
            if (curr.first > -1 && curr.first < 8 && curr.second > -1 && curr.second < 8 && gameBoard.pokemonsBoard[curr.first].GetPokemon(7 - curr.second) != '\0')
                return false;
        }
        return true;
    }
    if (cell1.second == cell2.second) // Kiểm tra 2 ô cùng cột
    {
        int hDirec = (cell1.first < cell2.first) ? 1 : -1;
        while (curr.first + hDirec != cell2.first)
        {
            curr.first += hDirec;
            if (curr.first > -1 && curr.first < 8 && curr.second > -1 && curr.second < 8 && gameBoard.pokemonsBoard[curr.first].GetPokemon(7 - curr.second) != '\0')
                return false;
        }
        return true;
    }
    return false;
}

// Nhận đầu vào là một vector chứa tọa độ của các ô trên bảng game Pokemon
// Và trả về một vector chứa tất cả các ô trên đường đi từ ô đầu tiên đến ô cuối cùng trong vector đầu vào
vector<pair<int, int>> DGame::Path(vector<pair<int, int>> v)
{
    int s = v.size();
    pair<int, int> curr = v[0];
    vector<pair<int, int>> path = {curr};
    for (int i = 1; i < s; i++)
    {
        // Kiểm tra ô hiện tại có cùng hàng/cùng cột với ô tiếp theo không
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

// Kiểm tra có đường nối nào giữa 2 ô không và trả về đường nối (nếu có)
vector<pair<int, int>> DGame::CheckMatching(pair<int, int> cell1, pair<int, int> cell2)
{
    // So sánh hai Pokemon có giống nhau không
    if (gameBoard.pokemonsBoard[cell1.first].GetPokemon(7 - cell1.second) != gameBoard.pokemonsBoard[cell2.first].GetPokemon(7 - cell2.second))
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
        if (gameBoard.pokemonsBoard[temp1.first].GetPokemon(7 - temp1.second) == '\0' && ExistsLine(cell1, temp1) && ExistsLine(temp1, cell2))
            return Path(vector<pair<int, int>>({cell1, temp1, cell2}));
        if (gameBoard.pokemonsBoard[temp2.first].GetPokemon(7 - temp2.second) == '\0' && ExistsLine(cell1, temp2) && ExistsLine(temp2, cell2))
            return Path(vector<pair<int, int>>({cell1, temp2, cell2}));

        // Ưu tiên 2: kiểm tra đường Z
        // Z ngang (chữ N)
        temp1 = cell1;
        while (temp2.second + vDirec != cell2.second)
        {
            temp1.second += vDirec;
            temp2.second += vDirec;
            if (gameBoard.pokemonsBoard[temp1.first].GetPokemon(7 - temp1.second) == '\0' && gameBoard.pokemonsBoard[temp2.first].GetPokemon(7 - temp2.second) == '\0' && ExistsLine(temp1, temp2) && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2))
                return Path(vector<pair<int, int>>({cell1, temp1, temp2, cell2}));
        }
        // Z dọc (chữ Z)
        temp1 = cell1;
        temp2 = {cell1.first, cell2.second};
        while (temp2.first + hDirec != cell2.first)
        {
            temp1.first += hDirec;
            temp2.first += hDirec;
            if (gameBoard.pokemonsBoard[temp1.first].GetPokemon(7 - temp1.second) == '\0' && gameBoard.pokemonsBoard[temp2.first].GetPokemon(7 - temp2.second) == '\0' && ExistsLine(temp1, temp2) && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2))
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
        while (temp1.second > -2 && temp1.second < 8 + 1)
        {
            if ((temp1.second == -1 || temp1.second == 8 || (gameBoard.pokemonsBoard[temp1.first].GetPokemon(7 - temp1.second) == '\0' && gameBoard.pokemonsBoard[temp2.first].GetPokemon(7 - temp2.second) == '\0')) && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2))
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
        while (temp1.second > -2 && temp1.second < 8 + 1)
        {
            if ((temp1.second == -1 || temp1.second == 8 || (gameBoard.pokemonsBoard[temp1.first].GetPokemon(7 - temp1.second) == '\0' && gameBoard.pokemonsBoard[temp2.first].GetPokemon(7 - temp2.second) == '\0')) && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2))
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
        while (temp1.first > -2 && temp1.first < 8 + 1)
        {
            if ((temp1.first == -1 || temp1.first == 8 || (gameBoard.pokemonsBoard[temp1.first].GetPokemon(7 - temp1.second) == '\0' && gameBoard.pokemonsBoard[temp2.first].GetPokemon(7 - temp2.second) == '\0')) && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2))
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
        while (temp1.first > -2 && temp1.first < 8 + 1)
        {
            if ((temp1.first == -1 || temp1.first == 8 || (gameBoard.pokemonsBoard[temp1.first].GetPokemon(7 - temp1.second) == '\0' && gameBoard.pokemonsBoard[temp2.first].GetPokemon(7 - temp2.second) == '\0')) && ExistsLine(cell1, temp1) && ExistsLine(temp2, cell2))
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

pair<pair<int, int>, pair<int, int>> DGame::FindPair() // Tìm cặp nối hợp lệ, trả về cặp đó (nếu có)
{
    for (int i = 0; i < 63; i++)
        if (gameBoard.pokemonsBoard[i % 8].GetPokemon(7 - (i / 8)) != '\0')
            for (int j = i + 1; j < 64; j++)
                if (gameBoard.pokemonsBoard[j % 8].GetPokemon(7 - (j / 8)) != '\0')
                {
                    pair<int, int> hint1 = {i % 8, i / 8};
                    pair<int, int> hint2 = {j % 8, j / 8};
                    if (CheckMatching(hint1, hint2) != vector<pair<int, int>>({}))
                        return pair<pair<int, int>, pair<int, int>>({hint1, hint2});
                }
    return pair<pair<int, int>, pair<int, int>>({});
}

void DGameBoard::RemoveCell(pair<int, int> cell) // Xoá ô trên bảng Pokemon
{
    // Xóa node khỏi list
    if (pokemonsBoard[cell.first].height == 0) // Nếu chỉ còn một node duy nhất trong cột
    {
        delete pokemonsBoard[cell.first].head;
        pokemonsBoard[cell.first].head = NULL;
        pokemonsBoard[cell.first].tail = NULL;
    }

    else
    {
        Node *curr = pokemonsBoard[cell.first].head;
        for (int i = 0; i < 7 - cell.second; i++)
            curr = curr->next;
        if (curr == pokemonsBoard[cell.first].head)
        {
            pokemonsBoard[cell.first].head = curr->next;
            if (pokemonsBoard[cell.first].head != NULL)
                pokemonsBoard[cell.first].head->prev = NULL;
        }
        else if (curr == pokemonsBoard[cell.first].tail)
        {
            pokemonsBoard[cell.first].tail = curr->prev;
            if (pokemonsBoard[cell.first].tail != NULL)
                pokemonsBoard[cell.first].tail->next = NULL;
        }
        else
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }
        delete curr;
    }
    pokemonsBoard[cell.first].height--;

    // Xóa các cạnh và góc nếu các ô xung quanh đều đã bị xóa
    Controller::SetConsoleColor(WHITE, BLUE);
    int k = 0; // Nếu pokemonsBoard[cell.first].height < 6 thì sẽ xóa góc trên của cột chứa ô bị xóa, nếu > 6 thì đó là cạnh trên của bảng nên không xóa
    if (pokemonsBoard[cell.first].height < 6)
    {
        for (int i = 0; i < 7; i++)
        {
            Controller::GoToXY(left + 1 + i + cell.first * 8, top + (6 - pokemonsBoard[cell.first].height) * 4);
            cout << background[(6 - pokemonsBoard[cell.first].height) * 4][1 + cell.first * 8 + i];
        }
        k = -1;
    }
    if (cell.first > 0 && pokemonsBoard[cell.first - 1].GetPokemon(pokemonsBoard[cell.first].height + 1) == '\0')
    {
        for (int i = k; i < 3; i++)
        {
            Controller::GoToXY(left + cell.first * 8, top + 1 + i + (6 - pokemonsBoard[cell.first].height) * 4);
            cout << background[1 + (6 - pokemonsBoard[cell.first].height) * 4 + i][cell.first * 8];
        }
    }
    if (cell.first < 7 && pokemonsBoard[cell.first + 1].GetPokemon(pokemonsBoard[cell.first].height + 1) == '\0')
    {
        for (int i = k; i < 3; i++)
        {
            Controller::GoToXY(left + 8 + cell.first * 8, top + 1 + i + (6 - pokemonsBoard[cell.first].height) * 4);
            cout << background[1 + (6 - pokemonsBoard[cell.first].height) * 4 + i][cell.first * 8 + 8];
        }
    }
}

void DInfoBoard::SaveData() // Lưu thông tin người chơi vào file HighScores.txt
{
    fstream f("HighScores.txt", ios::app);
    f << playerName << ',' << mode << ',' << score << '\n';
    f.close();
}

void DGame::LosingScreen(string reason) // Hiển thị màn hình thua và lí do
{
    system("cls");      // Xoá màn hình console
    system("color F0"); // Đặt lại nền màu trắng cho màn hình console
    Menu::PrintLogo();  // In logo game
    // Vẽ các hình chữ nhật để tạo khung cho màn hình thông báo và lựa chọn Yes, No; Hiển thị điểm số và lí do thua
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

    // Xử lí sự kiện nhấn phím
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
            PlaySound(TEXT("Sound/Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
            PlaySound(TEXT("Sound/Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
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

void DGame::WinningScreen() // Hiển thị màn hình thắng
{
    system("cls");      // Xoá màn hình hiện tại
    system("color F0"); // Đặt lại nền màu trắng cho màn hình console
    Menu::PrintLogo();  // In logo game
    // Vẽ các hình chữ nhật để tạo khung cho màn hình thông báo và lựa chọn Yes, No; Hiển thị điểm số của người chơi
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

    // Xử lí sự kiện nhấn phím
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
            PlaySound(TEXT("Sound/Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
            PlaySound(TEXT("Sound/Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
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

void DGame::ExitGame() // Hiển thị màn hình thoát trò chơi
{
    // Vẽ các hình chữ nhật để tạo khung cho màn hình thoát game và lựa chọn Yes, No
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

    // Xử lí sự kiện nhấn phím
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
            PlaySound(TEXT("Sound/Move.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
            PlaySound(TEXT("Sound/Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
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