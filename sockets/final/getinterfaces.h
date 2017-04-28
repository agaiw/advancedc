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

#endif
