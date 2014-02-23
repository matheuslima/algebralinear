CC=gcc
CFLAGS=-g -c
LDFLAGS=-lm

all: algebralinear

algebralinear: matriz.o gramSchmidt.o main.o
	$(CC) matriz.o gramSchmidt.o main.o -o algebralinear $(LDFLAGS)

matriz.o: matriz.c
	$(CC) $(CFLAGS) matriz.c

gramSchmidt.o: gramSchmidt.c
	$(CC) $(CFLAGS)  gramSchmidt.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o *~ algebralinear
