#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MY_PORT 9998
#define MAXBUF	1024

int main(int argc, const char *argv[])
{
	int numOfServerDescriptor;
	if((numOfServerDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Socket error");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in localExtremity;
	bzero(&localExtremity, sizeof(localExtremity));
	localExtremity.sin_family      = AF_INET;
	localExtremity.sin_port        = htons(MY_PORT);
	localExtremity.sin_addr.s_addr = INADDR_ANY;

	if(bind(numOfServerDescriptor, (struct sockaddr*)&localExtremity, sizeof(localExtremity)) != 0)
	{
		perror("Bind error");
		exit(EXIT_FAILURE);
	}

	if(listen(numOfServerDescriptor, 20) != 0)
	{
		perror("Listen error");
		exit(EXIT_FAILURE);
	}

	printf("Father pid [%d]\n", getpid());

	char buffer[MAXBUF];

	while(1)
	{
		struct sockaddr_in client;
		socklen_t addrlen = sizeof(client);
		int numOfConnectedDescriptor = accept(numOfServerDescriptor, (struct sockaddr*)&client, &addrlen);
		printf("%s:%d connected\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

                switch(fork())
		{
			case -1:
				perror("Fork error");
				exit(EXIT_FAILURE);

			case 0:
				close(numOfServerDescriptor);
				printf("Child pid [%d]\n", getpid());

				while(1)
				{
					int size = write(numOfConnectedDescriptor, buffer, read(numOfConnectedDescriptor, buffer, MAXBUF));
					printf("Received from child [%d] : \n", getpid());
                                        int j = dup(1);
					write(j, buffer, size); 

					if(size == 0)
					{
						close(numOfConnectedDescriptor);
						printf("The end of [%d]: \n", getpid());
						exit(1);
					}

					if(strstr(buffer,"/exit")==buffer)
					{
						printf("Child closed [%d]\n",getpid());
						close(numOfConnectedDescriptor);
						exit(0);
					}
				}

			default:
				close(numOfConnectedDescriptor);
				break;
		}
	}
}

/*
 *this code was written in part by Christian Toinard
 */
