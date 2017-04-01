#pierwsza reg zostanie uruchomiona, jesli ma zaleznosic zostana uruchomione
#cel: zaleznosc
#	polecenia potrzebne do stworzenia cel
CC=~/embedded_C/buildroot-build/host/usr/bin/i586-buildroot-linux-uclibc-gcc

all: main

#zbuduj plik sample_lib.o z pliku sample_lib.c
#gcc ruszy jesli plik sample_lib.o nie istnieje lub jest starsy niz sample_lib.c
sample_lib.o: sample_lib.c
	$(CC) -c -o sample_lib.o sample_lib.c

main.o: main.c
	$(CC) -c -o main.o main.c


#zbuduj plik main wykorzystujac plik main.o i sample_lib.o
main: main.o sample_lib.o
	$(CC) -o main main.o sample_lib.o

