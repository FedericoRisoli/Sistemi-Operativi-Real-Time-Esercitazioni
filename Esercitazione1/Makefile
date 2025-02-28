# Variabili
CC = gcc
CFLAGS = -Wall
LIB_NAME = libfasttrigo.a
OBJ = fast_trigo.o


all: esercitazione1

$(LIB_NAME): $(OBJ)
	ar rcs $(LIB_NAME) $(OBJ)

fast_trigo.o: fast_trigo.c fast_trigo.h
	$(CC) $(CFLAGS) -c fast_trigo.c -o fast_trigo.o


esercitazione1: main.o $(LIB_NAME)
	$(CC) $(CFLAGS) main.o -L. -lfasttrigo -lm -o esercitazione1


main.o: main.c fast_trigo.h
	$(CC) $(CFLAGS) -c main.c -o main.o


clean:
	rm -f *.o *.a esercitazione1
