CC=gcc

all: cpSimple

cpSimple : stdio.o test.c
	$(CC) -o cpSimple stdio.o test.c

stdio.o: stdio.c stdio.h
	$(CC) -c stdio.c

clean:
	rm -f test *.o
