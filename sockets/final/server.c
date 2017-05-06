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

#define PORT 56789

int main() {

  // Create socket for accepting connections
  int sock = makeSocket(PORT);
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
          int status =  readFromClient(request, i);
          if (status >= 0) {
            handleRequest(request, i, &active_fds);
          }
          free(request);
          }
      } // end if FD_ISSET
    }   // end for fd loop
  }     // end while 
  return 0;
}
