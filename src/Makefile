CC=g++
LD=g++

LIBS=-lncurses

OBJS=main.o snake.o
SRCS=main.cpp snake.cpp
HDRS=snake.h

EXEC=../rsnake

CFLAGS=-c -g -Wall
LDFLAGS=$(LIBS) -g -o $(EXEC)

all: compile link

compile: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) $(SRCS)

link: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)
