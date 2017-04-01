#include <stdio.h>
#include "sample_lib.h"


int moja_funkcja(int argc, char *argv[]){
	for(int i = 1; i < argc;i++){
		puts(argv[i]);
	}

	return 0;
}
