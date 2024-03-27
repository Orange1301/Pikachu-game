#include <iostream>
#include <conio.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

using namespace std;

int main() {
    int a = 2;
    a = (a + 4) % 5;
    cout << a;
    return 0;
}