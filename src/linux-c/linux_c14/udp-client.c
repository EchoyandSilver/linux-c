#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#define N 128

int main(int argc,const char *argv[])
{
	int sockfd;
	struct sockaddr_in serveraddr;
	
	char buf[] = {0};
	
	if(argc != 3){
		fprintf(stderr,"Usage:%s serverip port\n",argv[0]);
		return -1;
	}
	
	if(sockfd = socket(AF_INET,SOCK_DGRAM,0) < 0){
		perror("fail to socket");
		return -1;
	}
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));

	while(1)
	{
		fgets(buf,N,stdin);
		buf[strlen(buf) - 1] = '\0';
		if(sendto(sockfd,buf,N,0,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) < 0)
		{
			perror("fail to sendto");
			return -1;
		}
		
		if(strncmp(buf,"quit",4) == 0){
			break;
		}		
		
		if(recvfrom(sockfd,buf,N,0,NULL,NULL) < 0){
			perror("fail to recvfrom");
			return -1;
		}
		printf("server:%s\n",buf);
	}
	close(sockfd);
}
