#include <stdio.h>
#include <assert.h>

#include "getinterfaces.h"

int main() {

  ifDataS interfaces[4];
  ifDataS if1 = {"local",
                   "10.10.10.12",
                   "255.255.0.0",
                   "::1",
                   "DOWN",
                   "21:de:11:2c:33:07"};

  interfaces[0] = if1;
  ifDataS if2 = {"",
                   "",
                   "",
                   "",
                   "",
                   ""};

  interfaces[1] = if2;
  interfaces[2] = if2;
  interfaces[3] = if2;
  assert(getIfCount(interfaces) == 1);

  assert(getIfCount(interfaces) == 1555);







}
