#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#define N 128

int main(int argc,const char* argv[])
{
	int sockfd;
	struct sockaddr_in serveraddr, clientaddr;
	char buf[N] = {};	

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	if(argc != 3){
		fprintf(stderr,"Usage:%s serverip port\n",argv[0]);
		return -1;
	}
	
	if(sockfd < 0){
		perror("fail to socket");
		return -1;
	}
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));

	if(connect(sockfd,(struct sockaddr *)&serveraddr,sizeof(struct sockaddr)) < 0)
	{
		perror("fail to connect");
		return -1;
	}

	while(1)
	{
		fgets(buf,N,stdin);
		buf[strlen(buf)-1] = '\0';	
		send(sockfd,buf,N,0);

		if(strncmp(buf,"quit",4) == 0){
			break;
		}

		recv(sockfd,buf,N,0);
		printf("client:%s\n",buf);

	}
	close(sockfd);
}
