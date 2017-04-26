#ifndef _GETINTERFACES_H_
#define _GETINTERFACES_H_

typedef struct ifDataS {
  struct ifDataS* next;
  char ifName[16];
  char ipv4Addr[16];
  char ipv4Mask[16];
  char ipv6Addr[40];
  char status[5];
} ifDataS;

ifDataS* getIfData();

#endif
