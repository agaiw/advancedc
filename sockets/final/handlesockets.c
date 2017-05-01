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
    perror("Failed to create socket.");
    exit(EXIT_FAILURE);
  };

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(port);

  if (bind(sock_fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
    perror("Failed to bind socket.");
    exit(EXIT_FAILURE);
  }
  return sock_fd;
}

void readFromClient(char* request, int descriptor) {
  char* buffer = malloc(MAX_REQUEST * sizeof(char));
  strcpy(buffer, "");
  int len = read(descriptor, buffer, MAX_REQUEST);
  buffer[len] = '\0';
  if (len <= 0) {
    perror("Unable to read request from client.");
    exit(EXIT_FAILURE);
  }
  else {
    strcpy(request, buffer);
  }
  free(buffer);
  return;
}

void handleRequest(char* request, int descriptor, fd_set* active_fds) {
  ifDataS interfaces[IF_LIMIT];
  loadIfData(interfaces);
  int ifCount = getIfCount(interfaces);
  char* reply = (char*)malloc(MAX_RESPONSE * sizeof(char));
  if (strcmp(request, "getlist") == 0) {
    dumpInterfaceList(interfaces, reply);
  }
  else if (strcmp(request, "getall") == 0) {
    strcpy(reply, "");
    strcat(reply, "Details of available interfaces:\n");
    for (int i = 0; i < ifCount; ++i) {
      dumpInterface(interfaces, reply, interfaces[i].ifName);
      if ((ifCount - i) > 1) {
        strcat(reply, "\n");
      }
      strcat(reply, "\0");
    }
  }
  else if (strcmp(request, "error") == 0) {
    strcpy(reply, "Server encounered error.");
  }
  else {
    char* dest = malloc(11 * sizeof(char));
    strcpy(reply, "");
    strcpy(dest, "");
    strncpy(dest, request, 10);
    dest[10] = 0;
    if (strcmp(dest, "interface:") == 0) {
      int valid = 0;
      char* interface = (request + 10);
      int notFound = 1;
      for (int i = 0; i < ifCount; ++i) {
        if (strcmp(interface, interfaces[i].ifName) == 0) {
          dumpInterface(interfaces, reply, interface);
          notFound = 0;
          strcat(reply, "\0");
          break;
        }
      }
      if (notFound) {
        strcpy(reply, "Unknown interface.");
      }
    }
    else {
      strcpy(reply, "Unknown request.");
    }
  free(dest);
  }
  write(descriptor, reply, strlen(reply));
  free(reply);
  close(descriptor);
  FD_CLR(descriptor, active_fds);
}





