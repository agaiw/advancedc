#ifndef _HANDLESOCKETS_H_
#define _HANDLESOCKETS_H_

#define MAX_REQ 64 

int makeSocket(int port);

void readFromClient(char* request, int descriptor);

void handleRequest(char* request, int descriptor, fd_set* active_fds);

#endif
