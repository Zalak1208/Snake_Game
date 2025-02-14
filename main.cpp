#include <iostream>
#include "intro.h"
#include "map.h"
#include "snake.h"
#include <unistd.h>
#include <windows.h>
#include <ctime>
using namespace std;

int height = 40;
int width = 81;
int speed = 20;

int main()
{   
	srand(time(0));
	show_intro();
	instructions();	
	while(true)
	{
	Map map1(width, height);
	Snake snake1( height/2 , width/2 ,speed );
	map1.run(snake1);
	}
	return 0;
}
