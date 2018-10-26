#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>

#define MY_ADDR_IP "127.0.0.1"
#define MY_PORT 9999

int main(int argc, char **argv){

	int numberOfServerDescriptor, ip, b, l;

	struct sockaddr_in myLocalExtremity;
	myLocalExtremity.sin_family=AF_INET;
	myLocalExtremity.sin_port=htons(MY_PORT);
	if( (ip=inet_pton(AF_INET,MY_ADDR_IP,&myLocalExtremity.sin_addr))==0){
                printf("Invalid IP address\n");
                exit(EXIT_FAILURE);
	}
	else if(ip==-1){
		perror("Invalid address family");
		exit(EXIT_FAILURE);
	}
	
	if( (numberOfServerDescriptor = socket(AF_INET, SOCK_STREAM, 0))==-1){
		perror("Socket error");
		exit(EXIT_FAILURE);
	}
	
	printf("numberOfServerDescriptor = %i\n",numberOfServerDescriptor);
	
	if((b = bind(numberOfServerDescriptor, (const struct sockaddr *)&myLocalExtremity, sizeof(myLocalExtremity)))<0){
                perror("Bind error");
                exit(EXIT_FAILURE);
	}	

	if((l = listen(numberOfServerDescriptor, 1))<0){
                perror("Listen error");
                exit(EXIT_FAILURE);
	}

	while(1){}

	exit(EXIT_SUCCESS);
}

/*
 *this code was written in part by Christian Toinard
 */
