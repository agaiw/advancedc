all: client server

client: client.o
	gcc -o client client.o

server: server.o getinterfaces.o handlesockets.o
	gcc -o server server.o getinterfaces.o handlesockets.o

client.o: client.c
	gcc -c -o client.o client.c

server.o: server.c getinterfaces.h handlesockets.h
	gcc -c -o server.o server.c

getinterfaces.o: getinterfaces.c getinterfaces.h
	gcc -c -o getinterfaces.o getinterfaces.c

handlesockets.o: handlesockets.c handlesockets.h
	gcc -c -o handlesockets.o handlesockets.c

clean:
	-rm -rf *.o client server
