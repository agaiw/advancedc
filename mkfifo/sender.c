#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUF 1024

int main () {

  int fdsender;
  int fdreceiver;
  char* senderfifo = "/tmp/senderfifo";
  char* receiverfifo = "/tmp/receiverfifo";
  char buf[MAX_BUF];

  mkfifo(senderfifo, 0666);
  fdsender = open(senderfifo, O_WRONLY);
  write(fdsender, "Hi", sizeof("Hi"));
  close(fdsender);

  fdreceiver = open(receiverfifo, O_RDONLY);
  read(fdreceiver, buf, MAX_BUF);
  printf("sender.c: received answer: %s\n", buf);
  close(fdreceiver);

  return 0;

}
