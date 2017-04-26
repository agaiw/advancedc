#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include "getinterfaces.h"
#include <string.h>

ifDataS* getIfData() {

  struct ifaddrs* ifaddrs_p = NULL;
  getifaddrs(&ifaddrs_p);
  ifDataS* ifData_p = NULL;

  struct ifaddrs* currA = ifaddrs_p;
  ifDataS* currD = NULL;

  while (currA != NULL) {
    if(currD == NULL) {
      ifData_p =(ifDataS*)malloc(sizeof(ifDataS*));
      currD = ifData_p;
      strcpy(currD->ifName, currA->ifa_name);
      currD->next = NULL;
    } else {
      //check if interface already in list
      ifDataS* p = ifData_p;
      int alreadyAdded = 0;
      while (p != NULL) {
        if (p->ifName == currA->ifa_name) {
          alreadyAdded = 1;
          break;
        }
      }
      if(!alreadyAdded) {
        currD->next = (ifDataS*)malloc(sizeof(ifDataS*));
        currD = currD->next;
        strcpy(currD->ifName, currA->ifa_name);
        currD->next = NULL;
      }
    }
    currA = currA->ifa_next;
  };
  return ifData_p;
};

int main() {
  ifDataS* ifData_p = getIfData();
  while (ifData_p != NULL) {
    printf("interface: %s\n", ifData_p->ifName);
    ifData_p = ifData_p->next;
  }

  return 0;
}



