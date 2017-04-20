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
  struct sockaddr_un client;
  int sock_fd;
  int cli_sock_fd;
  size_t server_len;
  size_t client_len;

  sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  server.sun_family = AF_UNIX;
  strncpy(server.sun_path, "server_socket", strlen("server_socket"));
  server_len = sizeof(server); 

  bind(sock_fd, (struct sockaddr*)&server, server_len);

  listen(sock_fd, 5);

  client_len = sizeof(client);
  cli_sock_fd = accept(sock_fd, (struct sockaddr*)&client, (socklen_t*)&client_len);
  read(cli_sock_fd, buffer, 256);
  printf("server.c: message from client: %s\n", buffer);
  write(cli_sock_fd, "I got your message", strlen("I got your message"));
  close(cli_sock_fd);
  close(sock_fd);
  unlink("server_socket");
  return 0;

}
