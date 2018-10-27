/*
 * Exemple of use : gcc -D_POSIX_C_SOURCE=2001 -D_XOPEN_SOURCE=4 test_POSIX.c -o test_POSIX
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
	
	#ifdef _POSIX_SOURCE
        	printf("POSIX.1-1988 used\n");
	#endif
	
	if(_POSIX_C_SOURCE==1) printf("POSIX.1-1990 (1003.1) used\n");
	if(_POSIX_C_SOURCE==1993) printf("POSIX.1b-1993 used\n");
	if(_POSIX_C_SOURCE==1996) printf("POSIX.1c-1996 used\n");
	if(_POSIX_C_SOURCE==2001) printf("POSIX.1-2001 used\n");
	if(_XOPEN_SOURCE==1) printf("XPG3 used\n");
	if(_XOPEN_SOURCE==4) printf("XPG4 used\n");

	//Some sys constants
	
	printf("_SC_CHILD_MAX : %ld\n",sysconf(_SC_CHILD_MAX));
	printf("_SC_HOST_NAME_MAX : %ld\n",sysconf(_SC_HOST_NAME_MAX));
	printf("_SC_LOGIN_NAME_MAX : %ld\n",sysconf(_SC_LOGIN_NAME_MAX));
	printf("_SC_OPEN_MAX : %ld\n",sysconf(_SC_OPEN_MAX));
	printf("_SC_PAGESIZE : %ld\n",sysconf(_SC_PAGESIZE));
	printf("_SC_VERSION : %ld\n",sysconf(_SC_VERSION));
	exit(EXIT_SUCCESS);
}
