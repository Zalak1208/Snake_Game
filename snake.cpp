#include "snake.h"
#include <iostream>
#include <queue>
using namespace std;

Snake::Snake(int i, int j, int speed)
{
    pos.push({i, j});
    pos.push({i, j - 1});
    pos.push({i, j - 2});

    this->speed = speed;
    dir = 0;
    size = 3;

    /*
        3
      2   0
        1
        */
}

bool Snake::will_there_be_snake(int i, int j)
{
    queue<pair<int, int>> temp = pos;
    while (!temp.empty())
    {
        auto segment = temp.front();
        temp.pop();
        if (segment.first == i && segment.second == j)
        {
            return true;
        }
    }
    return false;
}

void Snake::grow()
{
    // Add a new segment at the tail
    pos.push(pos.back());
}
