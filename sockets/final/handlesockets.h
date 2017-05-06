#ifndef _HANDLESOCKETS_H_
#define _HANDLESOCKETS_H_

#define MAX_REQUEST 64 
#define MAX_RESPONSE 4096

/**
* Function:    makeSocket
* 
* Description: Creates new socket using provided
*              port number
*
* Parameters:  [in] port - number of port
*
* Returns:     File descriptor of created socket      
**/
int makeSocket(int port);

/**
* Function:    readFromClient
*
* Description: Reads incoming client request and puts it
*              into provided buffer
* Parameters:  [in/out] request - empty buffer to put client request in
*              [in] descriptor - file descriptor of particular client socket 
*
* Returns:     Length of read message or -1 in case of error
**/
int readFromClient(char* request, int descriptor);

/**
* Function:    handleRequest
*
* Description: This function reacts upon client request depending on
*              request content, sends the reply to client,
*              closes active file descriptor and removes it from active
*              client file descriptors array.
*              If request is valid, requested data is dumped and sent
*              to client. Otherwise error message is prepared and sent.
*
* Parameters:  [in] request - request from the client
*              [in/out] response - response to the client
*
* Returns:     void
**/
void createResponse(char* request, char* response);

#endif
