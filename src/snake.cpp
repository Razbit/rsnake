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

/*  snake.cpp - defines a bunch of functionality */

#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ncurses.h>

#include "snake.h"

using namespace std;

Snake::Snake(int speed=100)
{
	initscr(); //start curses mode
	cbreak(); //disable line buffering
	noecho(); //dont echo input to the screen
	timeout(1); //don't wait for the user's input for too long
	keypad(stdscr, TRUE); //enable arrow keys

	getmaxyx(stdscr, rows, cols); //get screen size

	food = 0;
	spawnFood();
	
	this->speed = speed;
	length = 2;
	curDir = DIR_RIGHT;

	//create the initial snake
	snakePiece init = {cols/2, rows/2};
	snakeBody.push_back(init);
	snakePiece temp = {(cols/2 +1), rows/2};
	snakeBody.push_back(temp);

	//and display the welcome message
	initWelcome();
}

Snake::~Snake()
{
	delete food;
	food = 0;
	endwin();
}

void Snake::displ()
{
	//clears screen, renders the snake
	initScreen();
	
	for (unsigned int i = 1; i < snakeBody.size(); i++)
	{
		mvprintw(snakeBody.at(i-1).y, snakeBody.at(i-1).x, bodyCh);
	}

	mvprintw(snakeBody.back().y, snakeBody.back().x, headCh);

	if (food)
		mvprintw(food->y, food->x, foodCh);
	
	refresh();
}

void Snake::initScreen()
{
	werase(stdscr);
	box(stdscr, 0, 0);
}

error_t Snake::move(dir_t dir)
{
	snakePiece temp; //a new temporary piece of the snake
	int origSpeed;

	switch(dir)
	{
	case DIR_UP:
		temp.x = snakeBody.back().x;
		temp.y = snakeBody.back().y - 1;
		break;
		
	case DIR_DOWN:
		temp.x = snakeBody.back().x;
		temp.y = snakeBody.back().y + 1;
		break;
		
	case DIR_LEFT:
		origSpeed = speed;
		
		if (speed > 60)
			speed -= 50; //compensate for line spacing

		temp.x = snakeBody.back().x - 1;
		temp.y = snakeBody.back().y;
		
		speed = origSpeed;
		break;
		
	case DIR_RIGHT:
		origSpeed = speed;
		
		if (speed > 60)
			speed -= 50; //compensate for line spacing
		
		temp.x = snakeBody.back().x + 1;
		temp.y = snakeBody.back().y;

		speed = origSpeed;
		break;
		
	case DIR_VOID:
		break;
	}

	if (temp.y < 1) //we are out of the screen..
		temp.y = rows-2;

	else if (temp.y > rows-2) //we are out of the screen..
		temp.y = 1;
	
   	else if (temp.x < 1) //we are out of the screen..
		temp.x = cols-2;
	
	else if (temp.x > cols-2) //we are out of the screen..
		temp.x = 1;

	//does the snake intersect with itself?
	bool intersect = false;
	for (unsigned int i = 0; i < snakeBody.size(); i++)
	{
		if (matches(temp, snakeBody.at(i)))
			intersect = true;
	}
	
	//if theres food at our "head", we shall eat it and become longer..
	if (food && matches(*food, temp))
	{
		eat();
		spawnFood(); //and add a new food! yay! FOOD
		length++;
    }

	else if (!intersect) //.. which means that we should not erase the "tail" piece
		snakeBody.erase(snakeBody.begin()); //erase first element

	if (intersect)
		return INTERSECT;
	
	snakeBody.push_back(temp);
	
	return NORMAL;
}

bool Snake::matches(snakePiece piece1, snakePiece piece2)
{
	if ((piece1.x == piece2.x) && (piece1.y == piece2.y))
		return true;
	
	return false;
}

bool Snake::matches(food_t itemFood, snakePiece itemSnake)
{
	if ((itemFood.x == itemSnake.x) && (itemFood.y == itemSnake.y))
		return true;
	
	return false;
}

dir_t Snake::getdir()
{
	//get input from user
	
	int ch = getch();
	dir_t ret;

	switch (ch)
	{
	case KEY_LEFT:
		ret = DIR_LEFT;
		break;
		
	case KEY_RIGHT:
		ret = DIR_RIGHT;
		break;
		
	case KEY_UP:
		ret = DIR_UP;
		break;
		
	case KEY_DOWN:
		ret = DIR_DOWN;
		break;
		
	case ERR:
	default:
		return DIR_VOID;	
	}

	//we can't turn around 180 degs at once! we would ourself if we did that..
	if (ret == DIR_LEFT && curDir == DIR_RIGHT)
		return DIR_VOID;
	
	else if (ret == DIR_RIGHT && curDir == DIR_LEFT)
		return DIR_VOID;
	
	else if (ret == DIR_UP && curDir == DIR_DOWN)
		return DIR_VOID;
	
	else if (ret == DIR_DOWN && curDir == DIR_UP)
		return DIR_VOID;
	else
		return ret;
}

void Snake::eat()
{
	//destroy the current food..
	delete food;
	food = 0;
	
	if (speed > 10) // the game shall not be too easy :D
		speed--; //it actually makes the snake go faster, just belive me..
}

void Snake::spawnFood()
{
	//find a non-snake-reserved position, spawn a food to it and set it as the cur food
	food_t* temp = new food_t;
	bool avail = false;
	
	while (!avail)
	{
		temp->x = rand() % (cols - 2); //generate a random position for our new, shiny food
		temp->y = rand() % (rows - 2);

		temp->x++; //and make sure it isn't inside the borders..
		temp->y++;
		
		avail = true;
		
		for (unsigned int i = 0; i < snakeBody.size(); i++) //and check that it doesn't intersect with our snake
		{
			if (temp->x == snakeBody.at(i).x && temp->y == snakeBody.at(i).y) {
				avail = false;
				break;
			}
		}
	}

	food = temp; //all tests passed, set as cur food
}

int Snake::getLen()
{
	return length; //returns th.. Well, i hope you know what this does.. :D
}

void Snake::initWelcome()
{
	char msg[] = "Welcome to Razbit's Rsnake!";
	int msglen = strlen(msg);

	mvprintw(8, (cols-msglen)/2, msg);
	refresh(); //updates curses
}

void Snake::displWelcome(int time)
{
	char msg[20];

	sprintf(msg, "Game will begin in %i..", time); //generates the message

	mvprintw(9, (cols - strlen(msg)) / 2, msg);
	refresh();
}

void Snake::gameOver()
{   // display game over message
	char msg_go[] = "Game over!";

	mvprintw(8, (cols - strlen(msg_go)) / 2, msg_go);

	char score[50];

	sprintf(score, "Score: %i", length);
	
	mvprintw(10, (cols - strlen(score)) / 2, score);
	
	char msg[] = "Press return to exit..";
	
	mvprintw(16, (cols - strlen(msg)) / 2, msg);
	refresh();

	
	timeout(0); //disable the timeout functionality
	            //actually, it makes getch() return ERR if no input is instantly available..
	
	while (true) //we wait for user to press return.. 
	{
		if (getch() == '\r' || getch() == '\n')
			break;
	}
}
