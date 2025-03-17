all: server client

server: server.o list.o
	gcc -o server server.o list.o

client: client.o
	gcc -o client client.o

server.o: server.c list.h
	gcc -c server.c

client.o: client.c
	gcc -c client.c

list.o: list.c list.h
	gcc -c list.c

clean:
	rm -f *.o server client
