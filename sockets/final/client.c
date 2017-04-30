#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>

int main() {

  char buffer[256];
  memset(buffer, 0, sizeof(buffer));
  struct sockaddr_in server;
  memset(&server, 0, sizeof(server));
  int sock_fd = 0;
  size_t server_len;

  if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("Failed to create socket.\n");
    return 1;
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(5000);
  server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if(connect(sock_fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
    printf("Failed to establish a connection with server.\n");
    return 1;
  }
  char message[] = "interface:lo";
  write(sock_fd, message, strlen(message));
  
  read(sock_fd, buffer, 256);
  printf("client.c: message from server: %s\n", buffer);
  close(sock_fd);
  return 0;

}
