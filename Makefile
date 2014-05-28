CC=gcc

all: test

test : stdio.o test.c
	$(CC) -c test.c

stdio.o: stdio.c stdio.h
	$(CC) -c stdio.c
