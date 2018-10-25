#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	extern char **environ;
	char **envi=environ;
	while(*envi){
		printf("%s\n",*envi++);
	}
	exit(EXIT_SUCCESS);
}
