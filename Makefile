CC=gcc
CFLAGS=-Wall

all:
	$(CC) nimzo.c functions.c -o nimzo
