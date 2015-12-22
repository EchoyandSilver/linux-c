#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#define N 128

int main(int argc,const char *argv[])
{
	int sockfd, acceptfd;
	struct sockaddr_in serveraddr,clientaddr;
	char buf[N];
	
	if(argc != 3){
		fprintf(stderr,"Usage:%s serverip port\n",argv[1]);
		return -1;
	}	

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
		perror("fail to socket");
		return -1;
	}
	
	printf("sockfd = %d\n",sockfd);
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));
	
	if(bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr)) < 0)
	{
		perror("fail to bind");
		return -1;
	}
	
	if(listen(sockfd,5) < 0)
	{	
		perror("fail to listen");
		return -1;
	}
	
	socklen_t addrlen = sizeof(struct sockaddr);

	if(acceptfd = accept(sockfd,(struct sockaddr*)&clientaddr,&addrlen) < 0)
	{
		perror("fail to accept");
		return -1;
	}

	while(1)
	{
		if(recv(acceptfd,buf,N,0) <= 0){
			perror("fail to recv");
			return -1;
		}	

		printf("server:%s\n",buf);
		if(strncmp(buf,"quit",4) == 0){
			break;
		}

		strcat(buf,"from server.");

		if(send(acceptfd,buf,N,0) < 0){
			perror("fail to send");
			return -1;
		}

	}	
	
	close(sockfd);
	close(acceptfd);

	return 0;
}
