CC = gcc
CFLAGS = -g -Wall -lm -std=c99

build: quadtree.c compress.h structs.h decompress.h
	$(CC) -o  quadtree quadtree.c  $(CFLAGS)
clean:
	rm -f quadtree

