#include "snake.h"
#include <iostream>
using namespace std;

Snake::Snake(int i, int j, int speed)
{
    this->pos = new int *[1];
    this->pos[0] = new int[2];

    this->pos[0][0] = i;
    this->pos[0][1] = j;

    this->speed = speed;
    dir = 0;
    size = 1;
    grow();
    grow();
    cout << "Snake created at " << pos[0][0] << " " << pos[0][1] << endl;
    /*
        3
      2   0
        1
        */
}

bool Snake::will_there_be_snake(int i, int j)
{
    for (int k = 0; k < size; k++)
    {
        if (pos[k][0] == i && pos[k][1] == j)
        {

            return true;
        }
    }
    return false;
}

void Snake::grow()
{
    int **new_pos = new int *[size + 1];
    for (int i = 0; i < size; i++)
    {
        new_pos[i] = new int[2];
        new_pos[i][0] = pos[i][0];
        new_pos[i][1] = pos[i][1];
    }
    new_pos[size] = new int[2];
    new_pos[size][0] = pos[size - 1][0];
    new_pos[size][1] = pos[size - 1][1];
    size++;
    delete[] pos;
    pos = new_pos;
}
