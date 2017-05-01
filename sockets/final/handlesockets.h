#ifndef _HANDLESOCKETS_H_
#define _HANDLESOCKETS_H_

#define MAX_REQUEST 64 
#define MAX_RESPONSE 4096
int makeSocket(int port);

void readFromClient(char* request, int descriptor);

void handleRequest(char* request, int descriptor, fd_set* active_fds);

#endif
