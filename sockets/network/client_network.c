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

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  server.sin_family = AF_INET;
  server.sin_port = htons(5000);
  server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  connect(sock_fd, (struct sockaddr*)&server, sizeof(server));

  write(sock_fd, "Hello, client is speaking", strlen("Hello, client is speaking"));
  
  read(sock_fd, buffer, 256);
  printf("client.c: message from server: %s\n", buffer);
  close(sock_fd);
  return 0;

}
