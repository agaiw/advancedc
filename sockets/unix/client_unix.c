#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main() {

  char buffer[256];
  memset(buffer, 0, 256);
  struct sockaddr_un server;
  int sock_fd;
  size_t server_len;

  sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  server.sun_family = AF_UNIX;
  strncpy(server.sun_path, "server_socket", strlen("server_socket"));
  server_len = sizeof(server); 

  connect(sock_fd, (struct sockaddr*)&server, server_len);

  write(sock_fd, "Hello, client is speaking", strlen("Hello, client is speaking"));
  
  read(sock_fd, buffer, 256);
  printf("client.c: message from server: %s\n", buffer);
  close(sock_fd);
  return 0;

}
