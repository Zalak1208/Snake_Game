#include "food.h"
using namespace std;

Food::Food(int x, int y)
{
    this->x = x;
    this->y = y;
}

Food::Food()
{
    x = 0;
    y = 0;
}

int Food::get_x()
{
    return x;
}

int Food::get_y()
{
    return y;
}

void Food::set_x(int x)
{
    this->x = x;
}

void Food::set_y(int y)
{
    this->y = y;
}