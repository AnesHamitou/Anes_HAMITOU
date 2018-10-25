#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	if(argc!=2){
		printf("\nUsage : %s <var>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	printf("\n%s = %s\n",argv[1],getenv(argv[1]));
	exit(EXIT_SUCCESS);
}
