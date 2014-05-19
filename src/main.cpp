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

/* main.cpp - defines entry point and main game loop*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "snake.h"

using namespace std;

int main(int argc, char **argv)
{
	time_t t1, t2;
	double dur;
	dir_t dir, tempDir;
	bool receivedDir = false;

	int speed = 100; //default speed

	if (argc >= 2) //if user gives a more preferred speed (as command-libne arg), we use that.
	{
		if (isdigit(argv[1][0])) //but only if it is a digit
			speed = atoi(argv[1]);
	}
	
	Snake* pSnake = new Snake(speed);
	pSnake->curDir = DIR_RIGHT;
	
	time(&t1); //get current time

	while (true) //show welcome message for 5 seconds
	{
	    time(&t2);
		dur = difftime(t2, t1); //calculate difference

		if (dur >= 5) // <-- that is the magic 5 :D
			break;
		
		pSnake->displWelcome((int)5-dur); //display welcome message with remaining time
	}

	pSnake->displ(); //display the (inital)snake

	time(&t1);
	
	while (true) //the main game loop
	{
		receivedDir = false;

		// we get <pSnake->speed> milliseconds of frametime (ncurses timeout is set to 1ms)
		for (int i = 0; i < pSnake->speed; i++) // this might seem weird ("Why not just a simple time delay? wtf..")
		{                                       // but I had problems with <sys/time>::gettimeofday()
			                                    // so its curses' delay doing the job..
			tempDir = pSnake->getdir(); //get input
			
			if (tempDir != DIR_VOID) //if no input was received, we keep the previous direction.
			{
				receivedDir = true; //we have received input, so DIR_VOID has no power anymore
				dir = tempDir;  //
			}
		}

		if (receivedDir) //if we received input..
			pSnake->curDir = dir; //..we set the new direction as the current one
		
	    //time to move the snake and do other thingys!
			
		if (pSnake->move(dir) == INTERSECT) //interscetion -> game over
		{
			pSnake->gameOver();			
			delete pSnake;
			return 0;
		}
			
		pSnake->displ(); //re-render the snake
	}

	return 0;
}

