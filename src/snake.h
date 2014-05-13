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
/*  snake.h - declares the snake and a bunch of functionality */

#ifndef _H_SNAKE
#define _H_SNAKE

#include <vector>

#define bodyCh "O"

struct snakePiece
{
	int x;
	int y;
};

enum error_t
{
	NORMAL,
	OUT_TOP,
	OUT_BOT,
	OUT_LEFT,
	OUT_RIGHT,
	INTERSECT
};

enum dir_t
{
	DIR_UP,
	DIR_DOWN,
	DIR_RIGHT,
	DIR_LEFT
};

class Snake
{
public:
	Snake();
	~Snake();

	error_t move(dir_t dir);
	void displ();
	
private:
	int score;
	int rows, cols;

	void addPiece(snakePiece);
	std::vector<snakePiece > snakeBody;
	void initScreen();
};

#endif //_H_SNAKE
