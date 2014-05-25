rsnake
======

Razbit's snake-ish game

How to build & run?
---------------------

Unfortunately, no Windows support at this moment. Feel free to contact me, if you have a viable solution for getting curses working on Windows.

UNIX -derivatives:
- Make sure you have g++, make and ncurses (libncurses-dev) installed. Then inside the rsnake directory run:

 make

Now you can run the game by typing:

 ./rsnake

If you want to, you can now copy the executable (rsnake) to a directory that is in your $PATH, so that you can run it more easily:
As root/using sudo:

 make install

The above copies the executable to /usr/local/bin/. If thats not where you want it, just type in (as root/using sudo):

 cp ./rnsnake </the/install/dir/>

Now you can run the game by just typing

 rsnake

A more detailed documentation can be found from the doc directory.

===========
Cheers,

Razbit
