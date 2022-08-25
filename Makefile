CC=gcc
CFLAGS=-ggdb -Wall
symbol_counter: main.c
	$(CC) -o symbol_counter main.c $(CFLAGS)
