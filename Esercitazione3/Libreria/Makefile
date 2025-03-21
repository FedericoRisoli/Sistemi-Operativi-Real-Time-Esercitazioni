all: server lettore casa

server: server.o list.o
	gcc -Wall -o server server.o list.o

lettore: lettore.o list.o
	gcc -Wall -o lettore lettore.o list.o

casa: casa.o list.o
	gcc -Wall -o casa casa.o list.o

casa.o: casa.c list.h
	gcc -Wall -c casa.c

server.o: server.c list.h
	gcc -Wall -c server.c

lettore.o: lettore.c list.h
	gcc -Wall -c lettore.c

list.o: list.c list.h
	gcc -Wall -c list.c

clean:
	rm -f *.o server lettore casa
