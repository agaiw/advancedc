#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include "getinterfaces.h"
#include "handlesockets.h"

int makeSocket(int port) {

  struct sockaddr_in server;
  memset(&server, 0, sizeof(server));

  int sock_fd = 0;

  if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Failed to create socket");
    exit(EXIT_FAILURE);
  };

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(port);

  if (bind(sock_fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
    perror("bind error");
    exit(EXIT_FAILURE);
  }
  return sock_fd;
}

void readFromClient(char* request, int descriptor) {
  char buffer[MAX_REQ];
  int len = read(descriptor, buffer, MAX_REQ);
  if (len <= 0) {
    perror("unable to read request from client");
    exit(EXIT_FAILURE);
  }
  else {
    strcpy(request, buffer);
  }
  return;
}

void handleRequest(char* request, int descriptor, fd_set* active_fds) {
  ifDataS interfaces[IF_LIMIT];
  loadIfData(interfaces);
  int ifCount = getIfCount(interfaces);
  char* reply;
  if (strcmp(request, "getlist") == 0) {
    reply = (char*)malloc(IF_ARRAY_SIZE + ifCount * IFDATA_IFNAME * sizeof(char));
    jsonizeInterfaceList(interfaces, reply);
}
  else if (strcmp(request, "getalldata") == 0) {
    reply = (char*)malloc(IF_ARRAY_SIZE + ifCount * IF_SIZE * sizeof(char));
    jsonizeAllInterfaces(interfaces, reply);
  }
  else if (strcmp(request, "error") == 0) {
    reply = "servererror";
  }
  else {
    char dest[11];
    strncpy(dest, request, 10);
    dest[10] = 0;
    if (strcmp(dest, "interface:") == 0) {
      int valid = 0;
      char* interface = (request + 10);
      for (int i = 0; i < ifCount; ++i) {
        if (strcmp(interface, interfaces[i].ifName) == 0) {
          reply = (char*)malloc(IF_SIZE * sizeof(char));
          jsonizeInterface(interfaces, reply, interface);
        }
      }
    }
    else {
      reply = "unknownrequest";
    }
    write(descriptor, reply, strlen(reply));
    close(descriptor);
    FD_CLR(descriptor, active_fds);
  }
}





