#ifndef SNAKE_H
#define SNAKE_H
#include <queue>
using namespace std;

class Snake
{
    public:
        int size;
        int dir;
        queue<pair<int, int>> pos;
        int speed;
        Snake(int i , int j , int speed);
        bool will_there_be_snake(int i, int j);
        void grow();
};
#endif