/*  This file is part of Rsnake, a snake-like game.

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
#include <cstdio>
#include <ncurses.h>

#include "snake.h"

using namespace std;

Snake::Snake()
{
	initscr();
	cbreak(); //disable line buffering
	noecho();
	halfdelay(1); //don't wait for the user's input for too long
	keypad(stdscr, TRUE);

	getmaxyx(stdscr, rows, cols);
	
	snakePiece init = {cols/2, rows/2};
	snakeBody.push_back(init);
	snakePiece temp = {cols/2, (rows/2 + 1)};
	snakeBody.push_back(temp);
}

Snake::~Snake()
{
	endwin();
}

void Snake::displ()
{
	//clears screen, renders the snake
	initScreen();
	
	for (unsigned int i = 0; i < snakeBody.size(); i++)
	{
	    mvprintw(snakeBody.at(i).y, snakeBody.at(i).x, bodyCh);
	}
	refresh();
}

void Snake::initScreen()
{
	werase(stdscr);
	box(stdscr, 0, 0);
}

error_t Snake::move(dir_t dir)
{
	snakePiece temp;

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
		temp.x = snakeBody.back().x - 1;
		temp.y = snakeBody.back().y;
		break;
		
	case DIR_RIGHT:
		temp.x = snakeBody.back().x + 1;
		temp.y = snakeBody.back().y;
		break;
	case DIR_VOID:
		break;
	}

	if (temp.y < 1) //we are out of the screen..
	{
		temp.y = rows-2;
	}

	else if (temp.y > rows-2) //we are out of the screen..
	{
		temp.y = 1;
	}

   	else if (temp.x < 1) //we are out of the screen..
	{
		temp.x = cols-2;
	}
	
	else if (temp.x > cols-2) //we are out of the screen..
	{
		temp.x = 1;
	}

	snakeBody.erase(snakeBody.begin()); //erase first element (the oldest one)

	//does the snake intersect with itself?
	bool intersect = false;
	for (unsigned int i = 0; i < snakeBody.size(); i++)
	{
		if (matches(temp, snakeBody.at(i)))
			intersect = true;
	}

	if (intersect)
		printw("INTERSECTION!");

	snakeBody.push_back(temp);
	
	return NORMAL;
}

bool Snake::matches(snakePiece piece1, snakePiece piece2)
{
	if ((piece1.x == piece2.x) && (piece1.y == piece2.y))
		return true;
	
	return false;
}

dir_t Snake::getdir()
{
	//fetch input from user
	
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

	//we can't turn around 180 degs at once!
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
