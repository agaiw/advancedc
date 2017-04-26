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
  struct sockaddr_in client;
  memset(&server, 0, sizeof(server));

  int sock_fd = 0;
  int cli_sock_fd = 0;
  size_t server_len;
  size_t client_len;

  if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("Failed to create socket.\n");
    return 1;
  };

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(5000);

  bind(sock_fd, (struct sockaddr*)&server, sizeof(server));

  listen(sock_fd, 10);
  client_len = sizeof(client);

  while(1) {
    cli_sock_fd = accept(sock_fd, (struct sockaddr*)&client, (socklen_t*)&client_len);
    read(cli_sock_fd, buffer, 256);
    printf("server.c: message from client: %s\n", buffer);
    write(cli_sock_fd, "I got your message", strlen("I got your message"));
    close(cli_sock_fd);
    sleep(1);
  }
  return 0;
}
