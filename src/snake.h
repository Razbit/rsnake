/*  COPYRIGHT EETU "RAZBIT" PESONEN, 2014

    This file is part of Rsnake, a snake-like game.

    Rsnake is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Rsnake is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Rsnake.  If not, see <http://www.gnu.org/licenses/>. */

/*  snake.h - declares the snake and a bunch of functionality */

#ifndef _H_SNAKE
#define _H_SNAKE

#include <vector>

#define bodyCh "O"
#define headCh "X"
#define foodCh "F"

struct snakePiece //all the data necessary to display a piece of the snake
{
	int x;
	int y;
};

struct food_t //all the data needed fot FOOD
{
	int x;
	int y;
};

enum error_t //the return type of the Snake::move()
{
	NORMAL, //normal operation, moving succeeded
	INTERSECT // we tried to eat ourself! how disgusting!
};

enum dir_t //the possible directions to go to
{
	DIR_UP,
	DIR_DOWN,
	DIR_RIGHT,
	DIR_LEFT,
	DIR_VOID //for invalidities in e.g. the input
};

class Snake
{
public:
	Snake(int); //constructor - sets up the snake
	~Snake();

	error_t move(dir_t dir); //moves the snake. Return NORMAL on success
	void displ(); //render the snake to the screen
	void initWelcome(); //init..
	void displWelcome(int time); //.. and display (and update) the welcome message
	dir_t getdir(); //get the new direction from the user
	int getLen(); //returns the length of the snake
	void gameOver(); //display the game over -message and score
	
	int speed; //the speed (10 is faster than 100)
	dir_t curDir; //the direction we are going
	
private:
	int rows, cols; //size of the screen
	int length; //len of the snake
	food_t* food; //the current food entity
	std::vector<snakePiece > snakeBody; //contains the snake's pieces

	void eat(); //eat the current food if we intersect with it
	void spawnFood(); //spawn a new food to the screen
	
	void addPiece(snakePiece); //add a new piece to the end of the snake
	void initScreen(); //sets up curses
	
	bool matches(snakePiece, snakePiece);
	bool matches(food_t, snakePiece);
};

#endif //_H_SNAKE
