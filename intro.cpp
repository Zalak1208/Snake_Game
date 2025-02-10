#include <iostream>
#include <windows.h> 
#include <conio.h>
#include "intro.h"
#include <iostream>

using namespace std;

void setCursorPosition(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(hConsole, position);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Hide cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = { 0, 0 };

    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        cellCount = csbi.dwSize.X * csbi.dwSize.Y;
        FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
        SetConsoleCursorPosition(hConsole, homeCoords);
    }
}

COORD getConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwSize;  // Returns width (X) and height (Y)
}

void show_intro() {
    hideCursor();
    COORD consoleSize = getConsoleSize();  // Get current window size
    int consoleWidth = consoleSize.X;
    int consoleHeight = consoleSize.Y;

    string intro_string1 = R"(
  /$$$$$$                      /$$                        /$$$$$$                                   
 /$$__  $$                    | $$                       /$$__  $$                                  
| $$  \__/ /$$$$$$$   /$$$$$$ | $$   /$$  /$$$$$$       | $$  \__/  /$$$$$$  /$$$$$$/$$$$   /$$$$$$ 
|  $$$$$$ | $$__  $$ |____  $$| $$  /$$/ /$$__  $$      | $$ /$$$$ |____  $$| $$_  $$_  $$ /$$__  $$
 \____  $$| $$  \ $$  /$$$$$$$| $$$$$$/ | $$$$$$$$      | $$|_  $$  /$$$$$$$| $$ \ $$ \ $$| $$$$$$$$
 /$$  \ $$| $$  | $$ /$$__  $$| $$_  $$ | $$_____/      | $$  \ $$ /$$__  $$| $$ | $$ | $$| $$_____/
|  $$$$$$/| $$  | $$|  $$$$$$$| $$ \  $$|  $$$$$$$      |  $$$$$$/|  $$$$$$$| $$ | $$ | $$|  $$$$$$$
 \______/ |__/  |__/ \_______/|__/  \__/ \_______/       \______/  \_______/|__/ |__/ |__/ \_______/
)";

    string press = "                                    Press any key to continue...";
    string intro_string2 = intro_string1 + "\n\n" + press;

    int textStartY = max(0, (consoleHeight - 10) / 2);  // Center vertically
    int textStartX = max(0, (consoleWidth - 80) / 2);   // Center horizontally

    for (int i = 0; i < 100000; ++i) {
        cout << "\033[2J\033[H";
        setCursorPosition(textStartX, textStartY);

        if (i % 30 > 15) {
            cout << "\033[36m"<< intro_string1 << "\033[0m";
        } else {
            cout << "\033[36m"<< intro_string2 << "\033[0m";
        }

        if (_kbhit()) {  // Break if key is pressed
            break;
        }
        Sleep(5);  // Controls the speed of the animation
    }

    // Final screen
    cout << "\033[2J\033[H";
    
}

void instructions()
{
    cout << "\033[32m" << "Use the arrow keys or WASD keys to move the snake." << endl << "\033[0m";
    cout << "\033[33m" << "Eat the food (@) to grow." << endl << "\033[0m";
    cout << "\033[32m" << "Avoid hitting the walls or yourself." << endl << "\033[0m";
    cout << "\033[33m" << "Press 'q' to quit." << endl << "\033[0m";
    cout << "\033[32m" << "Press any other key to play again." << endl << "\033[0m";
    Sleep(2000);
    char ch = _getch();
    //ch = _getch();
    while(true)
    {
        if(_kbhit())
        {
            char ch = _getch();
            if(ch == 'q')
            {
                exit(0);
            }
            else
            {
                break;
            }
        }
    }
}