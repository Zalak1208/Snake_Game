#include "map.h"
#include "snake.h"
#include "food.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
using namespace std;

void setCursorPosition1(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(hConsole, position);
}

int getMaxScore(const string &filename)
{
    std::ifstream inputFile(filename);
    int maxScore = 0;

    if (inputFile)
    {
        inputFile >> maxScore;
    }
    else
    {
        cerr << "No previous high score found. Starting fresh." << endl;
    }

    return maxScore;
}

void updateMaxScore(const string &filename, int newScore)
{
    std::ofstream outputFile(filename);
    if (outputFile)
    {
        outputFile << newScore;
    }
    else
    {
        cerr << "Error updating high score." << endl;
    }
}

Map::Map(int width, int height)
{
    this->width = width;
    this->height = height;
    map = new int *[height]; // ✅ Correct allocation order
    Food food(0, 0);
    for (int i = 0; i < height; i++)
    {
        map[i] = new int[width](); // ✅ Initialize with zeros
    }
}

void Map::draw(Snake &snake1)
{
    setCursorPosition1(0, 0);
    string s = "";
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width - 1)
            {
                s += "\033[33m#\033[0m";
            }
            else if ((i == 0 || i == height - 1) && j % 2 == 0)
            {
                s += "\033[33m#\033[0m";
            }
            else if (is_there_snake(i, j))
            {                
                s += Snake_body(i, j, i == snake1.pos[0][0] && j == snake1.pos[0][1]);
            }
            else if (map[i][j] == 2)
            {
                s += "\033[32m@\033[0m";
            }
            else
            {
                s += " ";
            }
        }
        s += '\n';
    }
    cout << s << endl
         << "Score: " << snake1.size * 10 - 30 << endl;
}

bool Map::is_there_snake(int i, int j)
{
    return map[i][j] == 1; // ✅ Simplified
}

string Map::Snake_body(int i, int j, bool is_head)
{
    if (is_head)
    {       
        return "\033[31m0\033[0m";
    }
    return "\033[35mO\033[0m";
}

void Map::update(Snake &snake1)
{
    int size = snake1.size;
    int **pos = snake1.pos;

    // ✅ Clear the previous snake position
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            map[i][j] = 0;
        }
    }
    if (food.get_x())
    {
        map[food.get_x()][food.get_y()] = 2;
    }

    // ✅ Update the map with the snake position
    for (int i = 0; i < size; i++)
    {
        int x = pos[i][0]; // Row index
        int y = pos[i][1]; // Column index

        if (x >= 0 && x < height && y >= 0 && y < width)
        {
            map[x][y] = 1; // ✅ Valid position
        }
        else
        {
            cout << "Error: Snake position out of bounds (" << x << ", " << y << ")" << endl;
        }
    }
}

void Map::print()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << map[i][j];
        }
        cout << endl;
    }
}

bool Map::move_snake(Snake &snake1)
{
    int **pos = snake1.pos;
    int size = snake1.size;
    int x = pos[0][0];
    int y = pos[0][1];
    int dir = snake1.dir;
    int new_x = x;
    int new_y = y;
    switch (dir)
    {
    case 0:
        new_y++;
        break;
    case 1:
        new_x++;
        break;
    case 2:
        new_y--;
        break;
    case 3:
        new_x--;
        break;
    }

    if (new_x < 1 || new_x >= height - 1 || new_y < 1 || new_y >= width - 1 || is_there_snake(new_x, new_y))
    {
        return false;
    }

    for (int i = size - 1; i > 0; i--)
    {
        pos[i][0] = pos[i - 1][0];
        pos[i][1] = pos[i - 1][1];
    }

    pos[0][0] = new_x;
    pos[0][1] = new_y;
    if (map[new_x][new_y] == 2)
    {
        snake1.grow();
        is_there_food = false;
        food.set_x(0);
        food.set_y(0);
    }

    if (_kbhit()) // Check if a key is pressed
    {
        char c = _getch(); // Get the pressed key
        if (c == -32)      // Special keys (arrow keys)
        {
            c = _getch(); // Get the actual arrow key code
            switch (c)
            {
            case 72:                 // Up arrow
                if (snake1.dir != 1) // Prevent reverse direction (down)
                    snake1.dir = 3;  // Up
                break;
            case 80:                 // Down arrow
                if (snake1.dir != 3) // Prevent reverse direction (up)
                    snake1.dir = 1;  // Down
                break;
            case 75:                 // Left arrow
                if (snake1.dir != 0) // Prevent reverse direction (right)
                    snake1.dir = 2;  // Left
                break;
            case 77:                 // Right arrow
                if (snake1.dir != 2) // Prevent reverse direction (left)
                    snake1.dir = 0;  // Right
                break;
            }
        }
        else // WASD keys
        {
            switch (c)
            {
            case 'w':                // W key for up
                if (snake1.dir != 1) // Prevent reverse direction (down)
                    snake1.dir = 3;  // Up
                break;
            case 's':                // S key for down
                if (snake1.dir != 3) // Prevent reverse direction (up)
                    snake1.dir = 1;  // Down
                break;
            case 'a':                // A key for left
                if (snake1.dir != 0) // Prevent reverse direction (right)
                    snake1.dir = 2;  // Left
                break;
            case 'd':                // D key for right
                if (snake1.dir != 2) // Prevent reverse direction (left)
                    snake1.dir = 0;  // Right
                break;
            }
        }
    }
    return true;
}

void Map::run(Snake &snake1)
{
    while (move_snake(snake1))
    {
        cout << "\033[2J\033[H";
        update(snake1);
        draw(snake1);
        if (!is_there_food)
        {
            generate_food();
        }
        Sleep(snake1.speed);
        snake1.speed = max(20, 200 - snake1.size * 5);
    }
    int maxScore = getMaxScore("highscore.txt");
    if (snake1.size * 10 - 30> maxScore)
    {
        updateMaxScore("highscore.txt", snake1.size * 10 - 30);
        maxScore = snake1.size * 10 - 30;
    }
    for (int i = 0; i < 100000; i++)
    {
        string Game_over = R"(
  ______                                            ______                                
 /      \                                          /      \
/$$$$$$  |  ______   _____  ____    ______        /$$$$$$  | __     __  ______    ______
$$ | _$$/  /      \ /     \/    \  /      \       $$ |  $$ |/  \   /  |/      \  /      \
$$ |/    | $$$$$$  |$$$$$$ $$$$  |/$$$$$$  |      $$ |  $$ |$$  \ /$$//$$$$$$  |/$$$$$$  |
$$ |$$$$ | /    $$ |$$ | $$ | $$ |$$    $$ |      $$ |  $$ | $$  /$$/ $$    $$ |$$ |  $$/
$$ \__$$ |/$$$$$$$ |$$ | $$ | $$ |$$$$$$$$/       $$ \__$$ |  $$ $$/  $$$$$$$$/ $$ |
$$    $$/ $$    $$ |$$ | $$ | $$ |$$       |      $$    $$/    $$$/   $$       |$$ |
 $$$$$$/   $$$$$$$/ $$/  $$/  $$/  $$$$$$$/        $$$$$$/      $/     $$$$$$$/ $$/
)";
        string text = "\033[31m" + Game_over + "\033[34m" + "\nYour score is " + to_string(snake1.size * 10 - 30) + "\nMax score is " + to_string(maxScore) + "\033[0m";
        cout << "\033[2J\033[H";
        cout << text << endl;
        // cout << "Your score is " << snake1.size*10 << endl;
        // cout << "Max score is " << maxScore << endl;
        if (i % 30 > 15)
        {

            cout << "\033[32m" << "Press q to quit" << endl;
            cout << "Press any other key to play again" << endl << "\033[0m";
        }
        if (_kbhit() )
        {
            char ch = _getch();
            if (ch == 'q')
            {
                exit(0);
            }
            else
            {
                break;
            }
        }
        Sleep(1);
    }
}

void Map::generate_food()
{
    int x = 1 + rand() % (height - 2);
    int y = 1 + rand() % (width - 2);
    if (map[x][y] == 0)
    {
        food.set_x(x);
        food.set_y(y);
        is_there_food = true;
        cout << "Food generated at " << x << " " << y << endl;
    }
    else
    {
        generate_food();
    }
}
