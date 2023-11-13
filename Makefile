CC = gcc

all: P0

P0: tree.c
	gcc -std=c99 -o P0 tree.c

clean:
	$(RM) P0