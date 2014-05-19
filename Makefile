CC=g++
LD=g++

LIBS=-lncurses

OBJS=main.o snake.o
SRCS=src/main.cpp src/snake.cpp
HDRS=src/snake.h

EXEC=rsnake
INSTALL_DIR=/usr/local/bin/

CFLAGS=-c -g -Wall
LDFLAGS=$(LIBS) -g -o $(EXEC)

all: compile link

install: all
	cp $(EXEC) $(INSTALL_DIR)

compile: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) $(SRCS)

link: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)
