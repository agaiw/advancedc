#ifndef _GETINTERFACES_H_
#define _GETINTERFACES_H_
#define IF_LIMIT 10

/**
* Structure:   ifDataS
*
* Description: Structure containing data of single
*              network interface
**/
typedef struct ifDataS {
  char ifName[16];
  char ipv4Addr[16];
  char ipv4Mask[16];
  char ipv6Addr[40];
  char status[5];
  char hwAddr[18];
} ifDataS;

/**
* Function:    loadIfData
*
* Description: Reads data of network interfaces available at server
*              and puts it into provided buffer
*
* Parameters:  [in/out] interfaces - empty array to put network
*              interfaces data in
*
* Returns:     void
**/
void loadIfData(ifDataS interfaces[]);

/**
* Function:    dumpInterfaceList
*
* Description: Puts names of all network interfaces which are available
*              at server into empty buffer
*
* Parameters:  [in] interfaces - array containing data of all
*              network interfaces available at server
*              [in/out] out - output dump string
* Returns:     void
**/
void dumpInterfaceList(ifDataS interface[], char* out);

/**
* Function:    dumpInterface
*
* Description: Puts data of single network interface into provided
*              empty buffer, taking network interfaces structure
*              as data source
*
* Parameters:  [in] interfaces - array containing data of all
*              network interfaces available at server
*              [in/out] out - output dump string
*              [in] ifName - interface to be dumped
*
* Returns:     void
**/
void dumpInterface(ifDataS interfaces[], char* out, char* ifName);

/**
* Function:    getIfCount
*
* Description: Calculates number of network interfaces available on server
*              using structure containing data of all interfaces
*
* Parameters:  [in] interfaces - array containing data of all
*              network interfaces available at server
*
* Returns:     Number of network interfaces
**/
int getIfCount(ifDataS interface[]);

#endif
