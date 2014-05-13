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

	getmaxyx(stdscr, rows, cols);
	
	snakePiece init = {cols/2, rows/2};
	snakeBody.push_back(init);
	snakePiece temp = {cols/2, (rows/2 + 1)};
	snakeBody.push_back(temp);
}

Snake::~Snake()
{
	getch();
	endwin();
}

void Snake::displ()
{
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
	snakeBody.push_back(temp);
	
	return NORMAL;
}
