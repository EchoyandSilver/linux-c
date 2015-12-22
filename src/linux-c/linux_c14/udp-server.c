#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define N 128

int main(int argc, const char *argv[])
{
	int sockfd;
	struct sockaddr_in serveraddr,clientaddr;
	socklen_t addrlen = sizeof(clientaddr);
	int nbyte;

	char buf[N] = {0};
	
	if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0){
		perror("fail to socket");
		return -1;
	}
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));
	
	if(bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) < 0){
		perror("fail to bind");
		return -1;
	}

	while(1)
	{
		if((recvfrom(sockfd,buf,N,0,(struct sockaddr*)&clientaddr,&addrlen)) < 0){
			perror("fail to recv");
			return -1;
		}	
			
		printf("client:%s --> %d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
		printf("client:%s\n",buf);

		if(strncmp(buf,"quit",4) == 0){
			break;
		}		
	
		strcat(buf,"from server.");	

		if(sendto(sockfd,buf,N,0,(struct sockaddr*)&clientaddr,addrlen) < 0){
			perror("fail to sento");
			return -1;
		}	

	}
	close(sockfd);
}
