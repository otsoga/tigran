CC=gcc
CFLAGS=-Wall

all:
	$(CC) tigran.c move.c input.c board.c rules.c log.c display.c -o tigran
