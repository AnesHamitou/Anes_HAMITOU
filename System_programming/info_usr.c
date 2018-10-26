/*
 * To test for the whole system users : in a terminal
 * for i in `cut -d : -f 1 /etc/passwd`; do ./info_usr -l $i; done
 */

#include<stdio.h>
#include<stdlib.h>
#include<pwd.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>

extern int errno;

int main(int argc, char **argv){
	struct passwd *pw;
	if(argc!=3){
		printf("USAGE : %s [-l|-u] <login>|<uid>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if(strcmp(argv[1],"-l")==0){
		if( (pw=getpwnam(argv[2]))==NULL){
			if(!errno){
				printf("User not found\n");
				exit(EXIT_FAILURE);
			}
			else {
				perror("Error getpwnam");
				exit(EXIT_FAILURE);
				}
		}
		printf("\n\nUsername : %s\n",pw->pw_name);
		printf("Password : %s\n",pw->pw_passwd);
		printf("UID : %d\n",pw->pw_uid);
		printf("GID : %d\n",pw->pw_gid);
		printf("Home : %s\n",pw->pw_dir);
		printf("User info : %s\n",pw->pw_gecos);
		printf("Shell : %s\n",pw->pw_shell);
	}

	else if(strcmp(argv[1],"-u")==0){
                if( (pw=getpwuid(atoi(argv[2])))==NULL){
                        if(!errno){
                                printf("User not found\n");
                                exit(EXIT_FAILURE);
                        }
                        else {
                                perror("Error getpwnam");
                                exit(EXIT_FAILURE);
                                }
                }
                printf("\n\nUsername : %s\n",pw->pw_name);
                printf("Password : %s\n",pw->pw_passwd);
                printf("UID : %d\n",pw->pw_uid);
                printf("GID : %d\n",pw->pw_gid);
                printf("Home : %s\n",pw->pw_dir);
                printf("User info : %s\n",pw->pw_gecos);
                printf("Shell : %s\n",pw->pw_shell);
        }
	else{
		printf("USAGE : %s [-l|-u] <login>|<uid>\n", argv[0]);
	}
	exit(EXIT_SUCCESS);
}
