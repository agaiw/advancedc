# below CC variable is used instead of gcc in case when cross compiler shall be used
CC=~/embedded_C/buildroot-build/host/usr/bin/i586-buildroot-linux-uclibc-gcc

all: main

# gcc will make target when sample_lib.o file does not 
# exist or is older than sample_lib.c
sample_lib.o: sample_lib.c
	gcc -c -fpic  -Werror -Wall -o sample_lib.o sample_lib.c

libsample_lib.so: sample_lib.o
	gcc -shared -o libsample_lib.so sample_lib.o

main.o: main.c
	gcc -c -o main.o main.c

main: main.o libsample_lib.so
	gcc -L/home/user/Documents/advancedc -Wall -o main main.o -lsample_lib

# -rm - minus sign here to ignore command warnings/errors
# like for example lack of patterned files
clean:
	-rm -rf *.o *.so
