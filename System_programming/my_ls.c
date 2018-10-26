/*
 * This program implements the "ls" command
 * it manages links, file lists (when the input is "*"), recursive calls are not managed yet.
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<pwd.h>
#include<grp.h>
#include<errno.h>
#include<time.h>
#include<dirent.h>
#include<string.h>

#define MAXBUFF 256

extern int errno;

void myls(char *, int);
void print_dir(char *);

void print_dir(char *dir_name){
        DIR *current_dir;
        struct dirent *s_dir;
        if((current_dir=opendir(dir_name))==NULL){
                perror("Couldn't open directory");
                exit(EXIT_FAILURE);
        }
        errno=0;
        while((s_dir=readdir(current_dir))){
                if( (strcmp(s_dir->d_name,".")) && (strcmp(s_dir->d_name,"..")) )
                        myls(s_dir->d_name,0);
        }
        if(errno){
                perror("Readdir error");
                exit(EXIT_FAILURE);
        }
}

void myls(char *name, int recursive){

	if(strcmp(name,"*")==0) print_dir("."); //File list
	else 
	{
		char time_var[MAXBUFF];
		char parent_file[MAXBUFF]; //For links
		struct stat info;
		struct passwd *user;
		struct group *gr;
		if(lstat(name,&info) < 0){
			perror("lstat error");
			exit(EXIT_FAILURE);

		}

		//TYPE
		if(S_ISLNK(info.st_mode)){
			int returned = readlink(name,parent_file,MAXBUFF);
			if(returned<0){
				perror("Readlink error");
				exit(EXIT_FAILURE);
			}
			parent_file[returned]='\0';
			printf("\nFile name : %s -> %s\n",name,parent_file);
		}
		else printf("\nFile name : %s\n",name);
		printf("Type : ");
		if(S_ISREG(info.st_mode)) printf("-");
		else if(S_ISDIR(info.st_mode)) printf("d");
		else if(S_ISLNK(info.st_mode)) printf("l");
		else if(S_ISCHR(info.st_mode)) printf("c");
		else if(S_ISBLK(info.st_mode)) printf("b");
		else if(S_ISFIFO(info.st_mode)) printf("f");
		else if(S_ISSOCK(info.st_mode)) printf("s");
		else printf("?");

		printf("\nRights : ");
		//RIGHTS
		(info.st_mode&S_IRUSR)?printf("r"):printf("-");
		(info.st_mode&S_IWUSR)?printf("w"):printf("-");
		(info.st_mode&S_IXUSR)?printf("x"):printf("-");

		(info.st_mode&S_IRGRP)?printf("r"):printf("-");
		(info.st_mode&S_IWGRP)?printf("w"):printf("-");
		(info.st_mode&S_IXGRP)?printf("x"):printf("-");

		(info.st_mode&S_IROTH)?printf("r"):printf("-");
		(info.st_mode&S_IWOTH)?printf("w"):printf("-");
		(info.st_mode&S_IXOTH)?printf("x"):printf("-");
		printf(" ");

		printf("\nInode number : %d\n",(int)info.st_ino);
		printf("ID of device containing the file : %d\n",(int)info.st_dev);
		printf("Number of hard links : %d\n",(int)info.st_nlink);
		printf("User : %d",(int)info.st_uid);
		if((user=getpwuid(info.st_uid))==NULL){
			perror("getpwuid call");
			exit(EXIT_FAILURE);
		}
		printf("(%s) \n",user->pw_name);
		printf("Group : %d",(int)info.st_gid);
		if((gr=getgrgid(info.st_gid))==NULL){
			perror("getgrgid call");
			exit(EXIT_FAILURE);
		}
		printf("(%s) \n",gr->gr_name);
		printf("Total size, in bytes : %d\n",(int)info.st_size);
		printf("Number of 512B blocks allocated : %d\n",(int)info.st_blocks);
		printf("Block size for filesystem I/O : %d\n",(int)info.st_blksize);

		strftime(time_var,MAXBUFF,"%d/%m/%y %H:%M:%S",localtime(&info.st_mtime));	
		printf("Time of last modification : %s ",time_var);
		printf("\n");
	}
}

int main(int argc, char **argv){

	if( (argc < 2) || (argc > 3) ){
		printf("Usage : %s <file> [-R]\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	if( (argc==3) && ( strcmp(argv[2],"-R") == 0 ) ){
		myls(argv[1], 1);	
	}
	else myls(argv[1], 0);

	exit(EXIT_SUCCESS);
}
