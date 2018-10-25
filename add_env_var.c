#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern int errno;

int main(int argc, char **argv){;
	if(argc!=3){
                printf("Usage : %s <VAR> <VALUE>\n",argv[0]);
                exit(EXIT_FAILURE);
        }
  int size = 2+strlen(argv[1])+strlen(argv[2]); //2 for '=' and '\0'
	char var[size];
	strcat(var,argv[1]);
	strcat(var,"=");
	strcat(var,argv[2]);
  if(!putenv(var)){
    perror("putenv error");
    exit(EXIT_FAILURE);
  }
	printf("Display :\n");
	extern char **environ;
	char **env=environ;
	while(*env) printf("%s\n",*env++);
	exit(EXIT_SUCCESS);
}
