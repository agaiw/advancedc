#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {

  // descriptors[0] is for reading
  // descriptors[1] is for writing
  int descriptors[2];
  int nbytes;

  pid_t childpid;

  char string[] = "Hello world\n";
  char readbuffer[80];

  // Create 2 descriptors for 2 end of pipe
  pipe(descriptors); 
  printf("Descriptor 1: %d, descriptor 2: %d\n", descriptors[0], descriptors[1]);

  if(-1 == (childpid = fork())) {

    // Print error in the following format:
    // fork: <system error msg>
    perror("fork");
    exit(1);

   }

  if (0 == childpid) {

    close(descriptors[0]);
    write(descriptors[1], string, (strlen(string) + 1));
    exit(0);

  } else {

    close(descriptors[1]);
    nbytes = read(descriptors[0], readbuffer, sizeof(readbuffer));
    printf("Received string: %s", readbuffer);
  }

  return 0;

}
