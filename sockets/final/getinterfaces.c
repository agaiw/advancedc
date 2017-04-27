#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include "getinterfaces.h"
#include <string.h>

void loadIfData(ifDataS interfaces[]) {

  // Initialize interfaces table
  for (int i = 0; i < IF_LIMIT; ++i) {
    strcpy(interfaces[i].ifName, "");
    strcpy(interfaces[i].ipv4Addr, "");
    strcpy(interfaces[i].ipv4Mask, "");
    strcpy(interfaces[i].ipv6Addr, "");
    strcpy(interfaces[i].status, "");
  }
  // Get interfaces data
  struct ifaddrs* ifaddrs_p = NULL;
  getifaddrs(&ifaddrs_p);

  struct ifaddrs* ifaddr = ifaddrs_p;

  while (ifaddr != NULL) {
    for (int i = 0; i < IF_LIMIT; ++i) { 
    if(strcmp(interfaces[i].ifName, ifaddr->ifa_name)) {
      printf("if\n");
      //interface already on the list
      break;
    } else if (strcmp(interfaces[i].ifName, "")) {
      printf("else\n");
      strcpy(interfaces[i].ifName, ifaddr->ifa_name);
      break;
      }
    }
    ifaddr = ifaddr->ifa_next;
  }
}

int main() {
  ifDataS interfaces[IF_LIMIT];
  loadIfData(interfaces);
  for (int i = 0; i < IF_LIMIT; ++i) {
    printf("interface: %s\n", interfaces[i].ifName);
  }

  return 0;
}



