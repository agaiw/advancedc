#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include "getinterfaces.h"
#include <string.h>
#include <net/if.h>

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
    for (int i = 0; i < IF_LIMIT; ++i) { 
    if(strcmp((char*)interfaces[i].ifName, ifaddr->ifa_name) == 0) {
      //interface already on the list
      break;
    } else if (strcmp((char*)interfaces[i].ifName, "") == 0) {
      strcpy(interfaces[i].ifName, ifaddr->ifa_name);
      break;
      }
    }
    for (int i = 0; i < IF_LIMIT; ++i) {
      if(strcmp((char*)interfaces[i].ifName, ifaddr->ifa_name) == 0) {
        if (ifaddr->ifa_addr->sa_family == AF_PACKET) {
        if (ifaddr->ifa_flags & (IFF_UP)) {
          strcpy(interfaces[i].status, "UP");
        }
        else {
          strcpy(interfaces[i].status, "DOWN");
        }
        }
        if(ifaddr->ifa_addr->sa_family == AF_INET) {
          struct sockaddr_in* sockaddr;
          sockaddr = (struct sockaddr_in*)ifaddr->ifa_addr;
          strcpy(interfaces[i].ipv4Addr, inet_ntoa(sockaddr->sin_addr));
          sockaddr = (struct sockaddr_in*)ifaddr->ifa_netmask;
          strcpy(interfaces[i].ipv4Mask, inet_ntoa(sockaddr->sin_addr));
        }
        if(ifaddr->ifa_addr->sa_family == AF_INET6) {
          struct sockaddr_in6* sockaddr = (struct sockaddr_in6*)ifaddr->ifa_addr;
          inet_ntop(AF_INET6, &sockaddr->sin6_addr, interfaces[i].ipv6Addr, sizeof(interfaces[i].ipv6Addr));
        }
      }
    }
    ifaddr = ifaddr->ifa_next;
  }
  for (int i = 0; i < IF_LIMIT; ++i) {
    if(strcmp(interfaces[i].ifName, "") != 0) {
      char path[40];
      memset(path, 0, sizeof(path));
      strcat(path, "/sys/class/net/");
      strcat(path, interfaces[i].ifName);
      strcat(path, "/address");
      FILE* fd;
      fd = fopen(path, "r");
      fgets(interfaces[i].hwAddr, sizeof(interfaces[i].hwAddr), fd);
      fclose(fd);
    }
  }
}


void printInterfaces(ifDataS interfaces[]) {
  printf("****************************************\n");
  for (int i = 0; i < IF_LIMIT; ++i) {
    if(strcmp((char*)interfaces[i].ifName, "") != 0) {
    printf("*** INTERFACE: %s ***\n \
           Status: %s\n \
           HW address: %s\n \
           IPv4 address: %s\n \
           IPv4 mask: %s\n \
           IPv6 address: %s\n",
           interfaces[i].ifName,
           interfaces[i].status,
           interfaces[i].hwAddr,
           interfaces[i].ipv4Addr,
           interfaces[i].ipv4Mask,
           interfaces[i].ipv6Addr);
    printf("****************************************\n");
    }
  }
}

void jsonizeInterface(ifDataS interfaces[], char* out, char* ifName) {
  for (int i = 0; i < IF_LIMIT; ++i) {
    if (strcmp(interfaces[i].ifName, ifName) == 0) {
      printf("interface to be jsonized: %s\n", ifName);
      strcpy(out, "");
      strcat(out, "{\"ifName\" : \"");
      strcat(out, interfaces[i].ifName);
      strcat(out, "\",\n\"status\" : \"");
      strcat(out, interfaces[i].status);
      strcat(out, "\",\n\"hwAddr\" : \"");
      strcat(out, interfaces[i].hwAddr);
      strcat(out, "\",\n\"ipv4Addr\" : \"");
      strcat(out, interfaces[i].ipv4Addr);
      strcat(out, "\",\n\"ipv4Mask\" : \"");
      strcat(out, interfaces[i].ipv4Mask);
      strcat(out, "\",\n\"ipv6Addr\" : \"");
      strcat(out, interfaces[i].ipv6Addr);
      strcat(out, "\"}\0");
      return;
    }
  }
}

void jsonizeInterfaceList(ifDataS interfaces[], char* out) {
  int ifCount = getIfCount(interfaces);
  strcpy(out, "");
  strcat(out, "{\"interfaces\" : [" );
  for (int i = 0; i < IF_LIMIT; ++i) {
    if (strcmp(interfaces[i].ifName, "") != 0) {
      strcat(out, "\"");
      strcat(out, interfaces[i].ifName);
      strcat(out, "\"");
    }
    if ((ifCount - i) > 1) {
      strcat(out, ", ");
    }
  }
  strcat(out, "] }\0");
  return;
}

void jsonizeAllInterfaces(ifDataS interfaces[], char* out) {
  int ifCount = getIfCount(interfaces);
  strcpy(out, "");
  strcat(out, "{\"interfacesData\" : [" );
  for (int i = 0; i < ifCount; ++i) {
    char* js = (char*)malloc(IF_SIZE*sizeof(char)); 
    jsonizeInterface(interfaces, js, interfaces[i].ifName);
    strcat(out, js);
    if ((ifCount - i) > 1) {
      strcat(out, ", ");
    }
    free(js);
  }
  strcat(out, "] }\0");
  return;
}

int getIfCount(ifDataS interfaces[]) {
  int ifCount = 0;
  for (int i = 0; i < IF_LIMIT; ++i) {
    if (strcmp(interfaces[i].ifName, "") != 0) {
      ++ifCount;
    }
  }
  return ifCount;
}
