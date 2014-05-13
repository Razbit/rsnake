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

	Snake snake;
	snake.curDir = DIR_RIGHT;
	
	gettimeofday(&t1, NULL);

	snake.displ();
	
	while (true)
	{
		gettimeofday(&t2, NULL); //get delay
		dur = (t2.tv_sec - t1.tv_sec) * 1000.0;
		dur += (t2.tv_usec - t1.tv_usec) / 1000.0;

		dir = snake.getdir(); //get input
		if (dir == DIR_VOID)
				dir = snake.curDir;
		else
			snake.curDir = dir;
		
		if (((snake.curDir == DIR_UP || snake.curDir == DIR_DOWN) && dur > snake.speed)
			|| ((snake.curDir == DIR_RIGHT || snake.curDir == DIR_LEFT) && dur > (snake.speed-50)))
		{
			snake.curDir = dir;
			
			snake.move(dir);
			snake.displ();
			gettimeofday(&t1, NULL);
		}
	}

	return 0;
}

