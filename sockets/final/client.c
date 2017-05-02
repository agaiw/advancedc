#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>

#define MAX_RESPONSE 4096
#define PORT 56789

void displayHelp(void);

int main(int argc, char* argv[]) {

  if ((argc < 2) || (strcmp(argv[1], "help") == 0)) {
    displayHelp();
    exit(EXIT_SUCCESS);
  }

  char buffer[MAX_RESPONSE];
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
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if(connect(sock_fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
    printf("Failed to establish a connection with server.\n");
    return 1;
  }
  printf("Request sent. Waiting for response from server...\n");
  write(sock_fd, argv[1], strlen(argv[1]));
  int readBytes;
  readBytes = read(sock_fd, buffer, MAX_RESPONSE);
  printf("Response from server received:\n");
  printf("%s\n", buffer);
  close(sock_fd);
  return 0;
}

void displayHelp() {
  printf("Usage options:\n");
  printf("./client getlist\t\tGet list of network interfaces available at server\n");
  printf("./client getall\t\t\tGet detailed information about interfaces\n");
  printf("./client interface:<interface>\tGet detailed information about selected interface\n");
  printf("./client help\t\t\tDisplay this help\n");
}
