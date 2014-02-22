CC=gcc
CFLAGS=-c

all: algebralinear

algebralinear: matriz.o gaussJordan.o main.o
	$(CC) matriz.o gaussJordan.o main.o -o algebralinear

matriz.o: matriz.c
	$(CC) $(CFLAGS) matriz.c

gaussJordan.o: gaussJordan.c
	$(CC) $(CFLAGS) gaussJordan.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o algebralinear
