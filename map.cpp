#include "map.h"
#include "snake.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <queue>
#include "food.h"
using namespace std;

int getMaxScore(const string &filename)
{
    ifstream inputFile(filename);
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
    ofstream outputFile(filename);
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
    map = new int *[height];
    Food food(0, 0);
    for (int i = 0; i < height; i++)
    {
        map[i] = new int[width](); 
    }
}

void Map::draw(Snake &snake1)
{
    string s = "";
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width - 1)
            {
                s += "#";
            }
            else if ((i == 0 || i == height - 1) && j % 2 == 0)
            {
                s += "#";
            }
            else if (is_there_snake(i, j))
            {
                s += Snake_body(i, j);
            }
            else if (map[i][j] == 2)
            {
                s += "F";
            }
            else
            {
                s += " ";
            }
        }
        s += '\n';
    }
    cout << s << endl
         << "Score: " << snake1.size * 10 << endl;
}

bool Map::is_there_snake(int i, int j)
{
    return map[i][j] == 1; 
}

char Map::Snake_body(int i, int j)
{
    return 'O';
}

void Map::update(Snake &snake1)
{
    // Clear the map
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            map[i][j] = 0;
        }
    }

    // Place food on the map
    if (food.get_x() >= 0 && food.get_y() >= 0)
    {
        map[food.get_x()][food.get_y()] = 2;
    }

    // Iterate over the snake's position queue
    queue<pair<int, int>> tempPos = snake1.pos; // Copy the queue for iteration
    while (!tempPos.empty())
    {
        pair<int, int> segment = tempPos.front();
        tempPos.pop();
        int x = segment.first;
        int y = segment.second;

        if (x >= 0 && x < height && y >= 0 && y < width)
        {
            map[x][y] = 1; // Mark snake's body on the map
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
    pair<int, int> head = snake1.pos.back(); // Get last element (head)
    int x = head.first;
    int y = head.second;
    int new_x = x, new_y = y;

    // Handle input before moving
    if (_kbhit())
    {
        char c = _getch();
        if (c == -32) { // Arrow keys
            c = _getch();
            switch (c)
            {
            case 72: if (snake1.dir != 1) snake1.dir = 3; break; // Up
            case 80: if (snake1.dir != 3) snake1.dir = 1; break; // Down
            case 75: if (snake1.dir != 0) snake1.dir = 2; break; // Left
            case 77: if (snake1.dir != 2) snake1.dir = 0; break; // Right
            }
        }
        else // WASD controls
        {
            switch (c)
            {
            case 'w': if (snake1.dir != 1) snake1.dir = 3; break;
            case 's': if (snake1.dir != 3) snake1.dir = 1; break;
            case 'a': if (snake1.dir != 0) snake1.dir = 2; break;
            case 'd': if (snake1.dir != 2) snake1.dir = 0; break;
            }
        }
    }

    // Determine new head position
    switch (snake1.dir)
    {
    case 0: new_y++; break; // Right
    case 1: new_x++; break; // Down
    case 2: new_y--; break; // Left
    case 3: new_x--; break; // Up
    }

    // Collision detection
    if (new_x < 1 || new_x >= height - 1 || new_y < 1 || new_y >= width - 1 || snake1.will_there_be_snake(new_x, new_y))
    {
        return false; // Collision
    }

    // Add new head position
    snake1.pos.push_back({new_x, new_y});

    // If food is found, grow snake; otherwise, remove tail
    if (map[new_x][new_y] == 2)
    {
        snake1.grow();
        is_there_food = false;
        food.set_x(-1); 
        food.set_y(-1);
    }
    else
    {
        snake1.pos.pop_front(); // Properly remove tail
    }

    return true;
}

void Map::run(Snake &snake1)
{
    while (move_snake(snake1))
    {
        cout << "\033[2J\033[H";  // Clear screen
        update(snake1);
        draw(snake1);
        
        if (!is_there_food)
        {
            generate_food();
        }
        
        Sleep(100); 
    }

    // After the game ends, display score
    int maxScore = getMaxScore("highscore.txt");
    if (snake1.size * 10 > maxScore)
    {
        updateMaxScore("highscore.txt", snake1.size * 10);
        maxScore = snake1.size * 10;
    }

    for (int i = 0; i < 100000; i++)
    {
        cout << "\033[2J\033[H";  // Clear screen
        cout << R"(
  ______                                            ______                                
 /      \                                          /      \
/$$$$$$  |  ______   _____  ____    ______        /$$$$$$  | __     __  ______    ______
$$ | _$$/  /      \ /     \/    \  /      \       $$ |  $$ |/  \   /  |/      \  /      \
$$ |/    | $$$$$$  |$$$$$$ $$$$  |/$$$$$$  |      $$ |  $$ |$$  \ /$$//$$$$$$  |/$$$$$$  |
$$ |$$$$ | /    $$ |$$ | $$ | $$ |$$    $$ |      $$ |  $$ | $$  /$$/ $$    $$ |$$ |  $$/ 
$$ \__$$ |/$$$$$$$ |$$ | $$ | $$ |$$$$$$$$/       $$ \__$$ |  $$ $$/  $$$$$$$$/ $$ |      
$$    $$/ $$    $$ |$$ | $$ | $$ |$$       |      $$    $$/    $$$/   $$       |$$ |      
 $$$$$$/   $$$$$$$/ $$/  $$/  $$/  $$$$$$$/        $$$$$$/      $/     $$$$$$$/ $$/       
)" << endl;

        cout << "Your score: " << snake1.size * 10 << endl;
        cout << "Max score: " << maxScore << endl;

        if (i % 30 > 15)
        {
            cout << "Press 'q' to quit" << endl;
            cout << "Press any other key to play again" << endl;
        }

        if (_kbhit())
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
    int x, y;
    bool foodPlaced = false;

    while (!foodPlaced)  
    {
        x = 1 + rand() % (height - 2);
        y = 1 + rand() % (width - 2);

        if (map[x][y] == 0)  
        {
            food.set_x(x);
            food.set_y(y);
            is_there_food = true;
            cout << "Food generated at " << x << ", " << y << endl;
            foodPlaced = true;
        }
    }
}
