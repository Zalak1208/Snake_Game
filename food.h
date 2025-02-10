# ifndef FOOD_H
# define FOOD_H

class Food
{
    private:
        int x;
        int y;
    public:
        Food(int x, int y);
        Food();
        int get_x();
        int get_y();
        void set_x(int x);
        void set_y(int y);
};

# endif