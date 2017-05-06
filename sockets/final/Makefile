all: client server

client: client.o
	$(CC) -o client client.o

server: server.o getinterfaces.o handlesockets.o
	$(CC) -o server server.o getinterfaces.o handlesockets.o

%.o: %.c
	$(CC) -c $^ -o $@ 

clean:
	-rm -rf *.o client server
