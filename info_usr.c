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
		printf("USAGE : ./exo14 [-l|-u] <login>|<uid>\n");
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
		printf("USAGE : ./exo14 [-l|-u] <login>|<uid>\n");
	}
	exit(EXIT_SUCCESS);
}
