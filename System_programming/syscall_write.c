#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<errno.h>
#include<string.h>

extern int errno;

int main(int argc, char **argv){
  int i=syscall(SYS_write,STDOUT_FILENO,"hello\n",6);
	if(i==-1){
    		//2 ways to manage errors :
    		printf("With perror\n");
		perror("SYS error ");
		printf("\nWith strerror\n");
		char *err=strerror(errno);
		printf("%s\n",err);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
