CC = gcc
CFLAGS = -Wall -Wpedantic -Werror

all: client server

client: client.o
	$(CC) $(CFLAGS) -o client client.o

server: server.o getinterfaces.o handlesockets.o
	$(CC) $(CFLAGS) -o server server.o getinterfaces.o handlesockets.o

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

clean:
	-rm -rf *.o client server
