#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>

#include "getinterfaces.h"
#include "handlesockets.h"

#define MAX_REQUEST 64
#define MAX_RESPONSE 4096

int main(int argc, char* argv[]) {

  if (argc < 2) {
    printf("Please provide valid port number (range: 1024-49151). Example usage:\n ");
    printf("./server 5100\n");
    exit(EXIT_SUCCESS);
  }
  int port = strtol(argv[1], NULL, 10);
  if (port < 1024 || port > 49151) {
   printf("Valid port number range: 1024-49151.\n"); 
   exit(EXIT_SUCCESS);
  }
  // Create socket for accepting connections
  int sock = makeSocket(port);
  if (listen(sock, 1) < 0) {
    perror("Failed to start listening on socket.");
    exit(EXIT_FAILURE);
  }

  // Initialize the set of active sockets
  fd_set active_fds, read_fds;
  FD_ZERO(&active_fds);
  FD_SET(sock, &active_fds);

  // Eternal loop for handling connections
  // and communicating with clients
  while (1) {
    read_fds = active_fds;
    if (select(FD_SETSIZE, &read_fds, NULL, NULL, NULL) < 0) {
      perror("Failed to select client socket.");
    }
    // Handle socket which have some pending information
    for (int i = 0; i < FD_SETSIZE; ++i) {
      if (FD_ISSET(i, &read_fds)) {
        if (i == sock) {
          // Connection request on original socket
          struct sockaddr_in clientname;
          size_t size = sizeof(clientname);
          int new = accept(sock,
                           (struct sockaddr*)&clientname,
                           (unsigned int*)&size);
          if (new < 0) {
            perror("Failed to accept connection.");
          }
          else {
            FD_SET(new, &active_fds);
          }
        } 
        else {
          // Pending data from already connected client

          char* request = (char*)malloc(MAX_REQUEST * sizeof(char));
          strcpy(request, "");
          int status =  readFromClient(request, MAX_REQUEST, i);
          if (status > 0) {
            char* response = (char*)malloc(MAX_RESPONSE * sizeof(char));
            response[0] = '\0';
            createResponse(request, response);
            write(i, response, strlen(response));
            free(response);
          }
          else {
            close(i);
            FD_CLR(i, &active_fds);
          }
          free(request);
        }
      } // end if FD_ISSET
    }   // end for fd loop
  }     // end while 
  return 0;
}
