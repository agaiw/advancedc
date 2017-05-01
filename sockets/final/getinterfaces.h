#ifndef _GETINTERFACES_H_
#define _GETINTERFACES_H_
#define IF_LIMIT 4

#define IFDATA_IFNAME 16
#define IF_SIZE 210
#define IF_ARRAY_SIZE 20 

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

void dumpInterface(ifDataS interfaces[], char* out, char* ifName);

void dumpInterfaceList(ifDataS interface[], char* out);

int getIfCount(ifDataS interface[]);

#endif
