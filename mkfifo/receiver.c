#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUF 1024

int main() {

  int fdsender;
  int fdreceiver;
  char* senderfifo = "/tmp/senderfifo";
  char* receiverfifo = "/tmp/receiverfifo";
  char buf[MAX_BUF];

  fdsender = open(senderfifo, O_RDONLY);
  read(fdsender, buf, MAX_BUF);
  printf("receiver.c: received message: %s\n", buf); 
  close(fdsender);

  mkfifo(receiverfifo, 0666); 
  fdreceiver = open(receiverfifo, O_WRONLY);
  write(fdreceiver, "So hi", sizeof("So hi"));
  close(fdreceiver);

  return 0;

}
