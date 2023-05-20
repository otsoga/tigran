CC=gcc
CFLAGS=-Wall

all:
	$(CC) tigran.c move.c input.c position.c rules.c log.c display.c pgn.c -o tigran
