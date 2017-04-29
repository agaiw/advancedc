#ifndef _GETINTERFACES_H_
#define _GETINTERFACES_H_
#define IF_LIMIT 4

typedef struct ifDataS {
  char ifName[16];
  char ipv4Addr[16];
  char ipv4Mask[16];
  char ipv6Addr[40];
  char status[5];
  char hwAddr[18];
} ifDataS;

void loadIfData(ifDataS interfaces[]);

void printInterfaces(ifDataS interfaces[]);

void jsonizeInterface(ifDataS interfaces[], char* jsonInterface, char* ifName);

void jsonizeInterfaceList(ifDataS interface[], char* jsonInterface);

int getIfCount(ifDataS interface[]);

#endif
