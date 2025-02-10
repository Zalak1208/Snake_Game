#ifndef MAP_H
#define MAP_H

#include "snake.h"
#include "food.h"
#include <queue>

class Map {
    private:
        int width;
        int height;
        int **map;
        bool is_there_food = false;
        Food food;

    public:
        Map(int width, int height);
        void draw(Snake& snake1);
        bool is_there_snake(int i, int j);
        char Snake_body(int i, int j);
        void update( Snake& snake1);
        void print();
        void run(Snake& snake1);
        bool move_snake(Snake& snake1);
        void generate_food();
};

#endif
