# Snake_Game
OG Snake Game in C++ in which the player controls the snake which is moving across the screen using W-A-S-D keys or arrow keys. The objective of the player is to maximize the score by eating food randomly generated on the screen. While players should avoid colliding with the walls and its own body. As the snake consumes food its length increases as well as its speed.

## Table of Contents
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Usage](#usage)
- [Conclusion](#conclusion)

## Dependencies
The following are the systems requirements:
- Windows 10 Operating System
- cpp compiler
- 13th Gen Intel(R) Core(TM) i5-13420H   2.10 GHz or Higher
- 4.0 GB RAM

## Installation
1) Clone this repository.
2) Open Command prompt.
3) Compile this code using the command: "g++ main.cpp intro.cpp map.cpp snake.cpp food.cpp".
4) Run a.exe file to play the game.
5) Read the instruction and play the game.

## Usage
Just run a.exe file.

## Features 
1) The game is played on a fixed-size grid, containing walls (boundaries), the snake, and the food.
2) The snake moves automatically in one direction until the player changes it.The snake can move left, right, up, or down, but it cannot move backward (e.g., if moving right, it cannot go left immediately).
3) The food is generated randomly on the grid, when the snake eats the food, its length increases by one segment. The new food is generated on a random location after being consumed. Each food item increases the player's score.
4) The game ends if the snake collides with the wall and with itself (its body).
5) The snake’s speed increases as it grows, making it harder to control.
6) High Score is stored and displayed after each loss. It is saved even after game is closed.


## Conclusion
The project is done with the concept of classes. There could more updates in the future based on the liking by the public.
