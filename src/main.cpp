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

/* main.cpp - defines entry point */

#include <cstdio>
#include <iostream>
#include <sys/time.h>

#include "snake.h"

using namespace std;

int main()
{
	timeval t1, t2;
	double dur;
	dir_t dir;

	Snake* pSnake = new Snake;
	pSnake->curDir = DIR_RIGHT;
	
	gettimeofday(&t1, NULL);

	while (true) //show welcome message
	{
		gettimeofday(&t2, NULL); //get delay
		dur = (t2.tv_sec - t1.tv_sec) * 1000.0;
		dur += (t2.tv_usec - t1.tv_usec) / 1000.0;

		if (dur > 5000)
			break;

		pSnake->displWelcome((int)(5-dur/1000.0));
	}

	pSnake->displ();
	
	while (true)
	{
		gettimeofday(&t2, NULL); //get delay
		dur = (t2.tv_sec - t1.tv_sec) * 1000.0;
		dur += (t2.tv_usec - t1.tv_usec) / 1000.0;

		dir = pSnake->getdir(); //get input
		if (dir == DIR_VOID)
				dir = pSnake->curDir;
		else
			pSnake->curDir = dir;
		
		if (((pSnake->curDir == DIR_UP || pSnake->curDir == DIR_DOWN) && dur > pSnake->speed)
			|| ((pSnake->curDir == DIR_RIGHT || pSnake->curDir == DIR_LEFT) && dur > (pSnake->speed-50)))
			//compensates the line spacing, thus such complication..
		{
			pSnake->curDir = dir;
			
			if (pSnake->move(dir) == INTERSECT)
			{
				pSnake->gameOver();
				pSnake->exit();
				
				delete pSnake;
				return 0;
			}
			
			pSnake->displ();
			
			gettimeofday(&t1, NULL);
		}
	}

	return 0;
}

