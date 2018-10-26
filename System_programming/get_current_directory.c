#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

extern int errno;

int main(int argc, char **argv){
	char pwd[1024];
	char *test;
	if((test=getcwd(pwd,1024))==NULL){
		perror("Getcwd error");
		exit(EXIT_FAILURE);
	}
	printf("Current working directory : %s\n",pwd);
	exit(EXIT_SUCCESS);
}
