#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

extern int errno;

void pr_pathconf(char *path, int name, char *message){
	/*
	 *path : path to the considered file
	 *name : the limit name
	 *message : the message to print
	 */
	long int limit=pathconf(path,name);
	if(limit<0){
		perror("Pathconf error");
		exit(EXIT_FAILURE);
	}
	printf("%s%ld\n",message,limit);
}

int main(int argc, char **argv){

	pr_pathconf(".",_PC_NAME_MAX,"The maximum length of a filename in the directory . : ");
	pr_pathconf("/",_PC_NAME_MAX,"The maximum length of a filename in the directory / : ");
	pr_pathconf("/etc/services",_PC_LINK_MAX,"The maximum number of links to the file /etc/services : ");
	pr_pathconf("/bin/rm",_PC_LINK_MAX,"The maximum number of links to the file /bin/rm : ");
	exit(EXIT_FAILURE);
}
