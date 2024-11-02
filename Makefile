# Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: main

main: src/main.o src/game_of_life.o
	$(CC) $(CFLAGS) -o main src/main.o src/game_of_life.o

main.o: src/main.c src/game_of_life.h
	$(CC) $(CFLAGS) -c main.c

game_of_life.o: src/game_of_life.c src/game_of_life.h
	$(CC) $(CFLAGS) -c src/game_of_life.c

clean:
	rm -f main src/main.o src/game_of_life.o
