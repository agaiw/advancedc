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
  };

 // Bind socket to port
  if (bind(sock_fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
    perror("Failed to bind socket.");
  }

  return sock_fd;
}

int readFromClient(char* request, int request_limit, int descriptor) {

  int len = read(descriptor, request, request_limit);

  if (len > 0) {
    request[len] = '\0';
  }

  return len;
}

void createResponse(char* request, char* response) {

  ifDataS interfaces[IF_LIMIT];
  loadIfData(interfaces);
  int ifCount = getIfCount(interfaces);
  int status = 0;

  // Valid request
  if (strcmp(request, "getlist") == 0) {
    dumpInterfaceList(interfaces, response);
  }
  // Valid request
  else if (strcmp(request, "getall") == 0) {
    strcpy(response, "");
    strcat(response, "Details of available interfaces:\n");
    for (int i = 0; i < ifCount; ++i) {
      dumpInterface(interfaces, response, interfaces[i].ifName);
      if ((ifCount - i) > 1) {
        strcat(response, "\n");
      }
      strcat(response, "\0");
    }
  }

  // Parsing other kinds of requests
  else {
    char* dest = malloc(11 * sizeof(char));
    strcpy(response, "");
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
          dumpInterface(interfaces, response, interface);
          notFound = 0;
          strcat(response, "\0");
          break;
        }
      }
      // ... but unknown interface
      if (notFound) {
        strcpy(response, "Unknown interface.");
      }
    }
    // Unknown request
    else {
      strcpy(response, "Unknown request.");
    }
  free(dest);
  }
}
