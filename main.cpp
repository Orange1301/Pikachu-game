#include <iostream>
#include <conio.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

using namespace std;

int main() {
    cout << "Hello Hello";
    while (true) {
        char c = getch();
        switch (c) {
            case UP:
                cout << "UP";
                break;
            case DOWN:
                cout << "DOWN";
                break;
            case LEFT:
                cout << "LEFT";
                break;
            case RIGHT:
                cout << "RIGHT";
                break;
            default:
                break;
        }
    }
    cout << endl;
    cout << "Hello world";
    cout << "abcxyz";
    return 0;
}