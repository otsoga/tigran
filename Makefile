CC=gcc
CFLAGS=-Wall

all:
	$(CC) tigran.c functions.c input.c board.c rules.c log.c -o tigran
