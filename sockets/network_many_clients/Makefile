all: client_network server_network_many_clients

client_network: client_network.o
	gcc -o client_network client_network.o

server_network_many_clients: server_network_many_clients.o
	gcc -o server_network_many_clients server_network_many_clients.o

client_network.o: client_network.c
	gcc -c -o client_network.o client_network.c

server_network_many_clients.o: server_network_many_clients.c
	gcc -c -o server_network_many_clients.o server_network_many_clients.c

clean:
	-rm -rf *.o client_network server_network_many_clients
