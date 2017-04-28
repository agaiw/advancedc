#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
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
  int family;

  while (ifaddr != NULL) {
    family = ifaddr->ifa_addr->sa_family;
    printf("family: %d\n", family);
    for (int i = 0; i < IF_LIMIT; ++i) { 
    if(strcmp((char*)interfaces[i].ifName, ifaddr->ifa_name) == 0) {
      //interface already on the list
      break;
    } else if (strcmp((char*)interfaces[i].ifName, "") == 0) {
      strcpy(interfaces[i].ifName, ifaddr->ifa_name);
      break;
      }
    }
    ifaddr = ifaddr->ifa_next;
    for (int i = 0; i < IF_LIMIT; ++i) {
      printf("i: %d\n", i);
      if(strcmp((char*)interfaces[i].ifName, ifaddr->ifa_name) == 0) {
        if(ifaddr->ifa_addr->sa_family == AF_INET) {
          struct sockaddr_in* sockaddr;
          sockaddr = (struct sockaddr_in*)ifaddr->ifa_addr;
          strcpy(interfaces[i].ipv4Addr, inet_ntoa(sockaddr->sin_addr));
        }
      }
    }
  }
}

int main() {
  ifDataS interfaces[IF_LIMIT];
  loadIfData(interfaces);
  for (int i = 0; i < IF_LIMIT; ++i) {
    printf("interface: %s, ipv4 address: %s\n",
           interfaces[i].ifName,
           interfaces[i].ipv4Addr);
  }

  return 0;
}



