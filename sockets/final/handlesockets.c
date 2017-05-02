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
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(port);

  // Create server socket
  if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Failed to create socket.");
    exit(EXIT_FAILURE);
  };

 // Bind socket to port
  if (bind(sock_fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
    perror("Failed to bind socket.");
    exit(EXIT_FAILURE);
  }

  return sock_fd;
}

void readFromClient(char* request, int descriptor) {

  int len = read(descriptor, request, MAX_REQUEST);
  request[len] = '\0';

  if (len <= 0) {
    perror("Unable to read request from client.");
    exit(EXIT_FAILURE);
  }

  return;
}

void handleRequest(char* request, int descriptor, fd_set* active_fds) {

  ifDataS interfaces[IF_LIMIT];
  loadIfData(interfaces);
  int ifCount = getIfCount(interfaces);
  char* reply = (char*)malloc(MAX_RESPONSE * sizeof(char));

  // Valid request
  if (strcmp(request, "getlist") == 0) {
    dumpInterfaceList(interfaces, reply);
  }
  // Valid request
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

  // Problem with server
  else if (strcmp(request, "error") == 0) {
    strcpy(reply, "Server encounered error.");
  }

  // Parsing other kinds of requests
  else {
    char* dest = malloc(11 * sizeof(char));
    strcpy(reply, "");
    strcpy(dest, "");
    strncpy(dest, request, 10);
    dest[10] = 0;

    // Valid request...
    if (strcmp(dest, "interface:") == 0) {
      int valid = 0;
      char* interface = (request + 10);
      int notFound = 1;
      for (int i = 0; i < ifCount; ++i) {

        //...and valid interface
        if (strcmp(interface, interfaces[i].ifName) == 0) {
          dumpInterface(interfaces, reply, interface);
          notFound = 0;
          strcat(reply, "\0");
          break;
        }
      }
      // ... but unknown interface
      if (notFound) {
        strcpy(reply, "Unknown interface.");
      }
    }
    // Unknown request
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
