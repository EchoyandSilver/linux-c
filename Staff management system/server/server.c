#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>
#include "head.h"

typedef struct sockaddr SA;
int     Info_rmark = 0;//文件Info.text互斥操作的读
int     Info_wmark = 0;//文件Info.text互斥操作的写
int     User_rmark = 0;//文件User.text互斥操作的读
int     User_wmark = 0;//文件User.text互斥操作的写

void findMsg(MSG *);
void findUser(MSG *);
void addMsg(MSG *);
void addUser(MSG *);
void delMsg(MSG *);
void delUser(MSG *);


void* handler(void * arg)
{
	MSG  msg;
	int n;
	int connfd = (int)arg;
	while(1)
	{
		n = recv(connfd,&msg, sizeof(MSG), 0);
		printf("get message from %s   type:%d  sign:%d\n",msg.name,msg.type,msg.sign);
		if(msg.type == QUIT)
		{
			printf("user %s quit!\n",msg.name);
			pthread_exit(NULL);
			close(connfd);
		}
		if(n == -1)
			break;
		if(msg.type == QUIT)
			break;
		getMsg(&msg);//取得客户端先要的信息，或者修改信息
		printf("send message to %s    type:%d   sign:%d\n\n",msg.name,msg.type,msg.sign);
		send(connfd,&msg, sizeof(MSG), 0);
	}

	close(connfd);
	pthread_exit(NULL);

}
int main(int argc, const char *argv[])//./server 192.168.1.16 6000
{
#if 0 
	USER user;
	strcpy(user.name,"zx");
	strcpy(user.passwd,"123");
	user.type = 11;
	user.no = 100;

	FILE * fp = fopen("./user.dat","wb");
	fwrite(&(user),sizeof(USER),1,fp);//写文件
	fclose(fp);
#endif

	int listenfd, connfd;
	
	struct sockaddr_in ser_addr, cli_addr;

	if(argc != 3)
	{
		printf("plz input %s <ip> <port>\n", argv[0]);
		exit(-1);
	}

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(-1);
	}

	bzero(&ser_addr, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(atoi(argv[2]));//"6000"
	ser_addr.sin_addr.s_addr = inet_addr(argv[1]);

	if(bind(listenfd, (SA *)&ser_addr, sizeof(ser_addr)) == -1)
	{
		perror("bind");
		exit(-1);
	}

	listen(listenfd, 5);

	bzero(&cli_addr, sizeof(cli_addr));
	socklen_t len = sizeof(cli_addr);
	printf("listenfd = %d\n", listenfd);


	while(1)
	{
		if((connfd = accept(listenfd, (SA *)&cli_addr, &len)) == -1)
		{
			perror("accept");
			exit(-1);
		}
		printf("connect with ip : %s, port : %d\n", 
				inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
		/*父进程接收客户端请求后，创建子进程与客户端通信*/

		pthread_t child_pthread;

		if(pthread_create(&child_pthread,NULL,handler,(void *)connfd) < 0)
		{
			perror("pthread_create");
			exit(1);
		}
	}

	close(listenfd);
	return 0;
}

int getMsg(MSG * msg)
{
	switch(msg->type)
	{
	case READ:
		findMsg(msg);
		break;
	case CHANGE:
		delUser(msg);
		addUser(msg);
		delMsg(msg);
		addMsg(msg);
		break;
	case ADD:
		addUser(msg);
		addMsg(msg);
		break;
	case DELETE:
		delUser(msg);
		delMsg(msg);
		break;
	case LOAD:
		findUser(msg);
		break;
	default:
		break;		
	}
	return 0;
}

void findMsg(MSG *msg)
{
	INFO info_temp;
	int flag = 0;
	FILE *fp;
 
	while(Info_wmark > 0) //实现读写文件的互斥
	{
		usleep(100000);
	}
	Info_rmark++;

	if((fp = fopen("./info.dat","rb")) == NULL)
	{
		printf("User %s requset:no file info.dat\n",msg->name);
		msg->sign = FAILED;
		strcpy(msg->data,"not file");
		return;
	}


	if(strcmp(msg->info.name,"null") != 0)//姓名不为空
	{
		while(fread(&info_temp,sizeof(INFO),1,fp) != 0)//读文件
		{
			if(strcmp(info_temp.name,msg->info.name) == 0)//比较名字是否相同
			{
				if(flag == 1)
				{
					if((msg->info.no != 0)&&(msg->info.no == info_temp.no))
					{//存在另个名字一样的员工，则进行编号的对比
					//如果一样则成功返回
						msg->info = info_temp;
						msg->sign = SUCCESS;
		    			strcpy(msg->data,"find it");
						return;
					}
					else
					{
						continue;//若编号不同则保留上一个员工信息
					}
				}
				msg->sign = SUCCESS;
				strcpy(msg->data,"find it");
				msg->info = info_temp;
				flag = 1;
			}

		}
		if(flag == 0)
		{
			msg->sign = FAILED;
		    strcpy(msg->data,"not find");
			return;
		}


	}
	else if(msg->info.no != 0)
	{
		while(fread(&info_temp,sizeof(INFO),1,fp) != 0)//读文件
		{
			if(info_temp.no == msg->info.no)//比较编号是否相同
			{
				if(flag == 1)
				{
					if((strcmp(msg->info.name,"null") != 0)&&(strcmp(msg->info.name,info_temp.name) == 0))
					{//存在另个编号一样的员工，则进行姓名的对比
						msg->info = info_temp;
						msg->sign = SUCCESS;
		    			strcpy(msg->data,"find it");
						return;
					}
					else
					{
						continue;//若姓名不同则保留上一个员工信息
					}
				}
				msg->info = info_temp;
				flag = 1;
			}

		}
		if(flag == 0)
		{
			msg->sign = FAILED;
			strcpy(msg->data,"not find");
			return;
		}

	}

	fclose(fp);
	Info_rmark--;

}
void addMsg(MSG *msg)
{
	FILE * fp;
	while((Info_wmark > 0)&&(Info_rmark > 0)) //实现读与写和读文件的互斥
	{
		usleep(100000);
	}
	Info_wmark++;

	if((fp = fopen("./info.dat","ab")) == NULL)
	{
		printf("User %s requset:open Info.text failed\n",msg->name);
		msg->sign = FAILED;
		strcpy(msg->data,"not file");
		return;
	}

	fwrite(&(msg->info),sizeof(INFO),1,fp) ;//写文件

	printf("add info for %s ok!\n",msg->name);

	msg->sign = SUCCESS;
	strcpy(msg->data,"write info ok!\n");

	fclose(fp);
	Info_wmark--;
}
void delMsg(MSG *msg)
{
	FILE * fp;
	int i = 0;
	INFO  info_temp[N];

	while(Info_wmark > 0) //实现读与写和读文件的互斥
	{
		usleep(100000);
	}
	Info_rmark++;

	if((fp = fopen("./info.dat","rb")) == NULL)
	{
		printf("User %s requset:open info.dat failed\n",msg->name);
		msg->sign = FAILED;
		strcpy(msg->data,"not file");
		return;
	}

	while(fread(&(info_temp[i++]),sizeof(INFO),1,fp) != 0)//读文件
	{
		;
	}
	fclose(fp);
	Info_rmark--;
	//向文件中写数据
	while((Info_wmark > 0)&&(Info_rmark > 0)) //实现读与写和读文件的互斥
	{
		usleep(100000);
	}
	Info_wmark++;

	if((fp = fopen("./info.dat","wb")) == NULL)
	{
		printf("User %s requset:open info.dat failed\n",msg->name);
		msg->sign = FAILED;
		strcpy(msg->data,"not file");
		return;
	}
	while(i--)
	{
		if(msg->info.no == info_temp[i].no)
			continue;
		fwrite(&(info_temp[i]),sizeof(INFO),1,fp);//写文件
	}


	printf("delete info for %s ok!\n",msg->name);

	msg->sign = SUCCESS;
	strcpy(msg->data,"change info ok!\n");

	fclose(fp);
	Info_wmark--;
}
void delUser(MSG *msg)
{
	FILE * fp;
	int i = 0;
	USER user_temp[N];

	while(User_wmark > 0) //实现读与写和读文件的互斥
	{
		usleep(100000);
	}
	User_rmark++;

	if((fp = fopen("./user.dat","rb")) == NULL)
	{
		printf("User %s requset:open user.dat failed\n",msg->name);
		msg->sign = FAILED;
		strcpy(msg->data,"not file");
		return;
	}
	while(fread(&(user_temp[i++]),sizeof(USER),1,fp) != 0)//读文件
	{
		;
	}
	fclose(fp);
	User_rmark--;

	//向文件中写数据
	while((User_wmark > 0)&&(User_rmark > 0)) //实现读与写和读文件的互斥
	{
		usleep(100000);
	}
	User_wmark++;

	if((fp = fopen("./user.dat","wb")) == NULL)
	{
		printf("User %s requset:open user.dat failed\n",msg->name);
		msg->sign = FAILED;
		strcpy(msg->data,"not file");
		return;
	}
	while(i--)
	{
		if(msg->info.no != user_temp[i].no)
			fwrite(&(user_temp[i]),sizeof(USER),1,fp);//写文件
	}

	msg->sign = SUCCESS;

	printf("delete user for %s  ok !\n",msg->name);

	strcpy(msg->data,"delete user ok!\n");

	fclose(fp);
	User_wmark--;
	
}
void findUser(MSG *msg)
{
	FILE * fp;
	int flag = 0;
	while(User_wmark > 0) //实现读与写和读文件的互斥
	{
		usleep(100000);
	}
	User_rmark++;

	if((fp = fopen("./user.dat","rb")) == NULL)
	{
		printf("User %s requset:no file user.dat\n",msg->name);
		msg->sign = FAILED;
		strcpy(msg->data,"not file");
		return;
	}

	USER user_temp;

	while(fread(&user_temp,sizeof(USER),1,fp) != 0)//读文件
		{
			if(strcmp(user_temp.name,msg->name) == 0)//比较名字是否相同
			{
				if(strcmp(msg->passwd,user_temp.passwd) == 0)
					{
						flag = 1;
						msg->sign = SUCCESS;
						msg->info.type = user_temp.type;
						msg->sign = SUCCESS;
		    			strcpy(msg->data,"all is right");
						return;
					}
			}

		}
		if(flag == 0)
		{
			msg->sign = FAILED;
		    strcpy(msg->data,"find user failed!\n");
			return;
		}

	fclose(fp);
	User_rmark--;

}
void addUser(MSG *msg)
{
	FILE * fp;
	USER user;
	strcpy(user.name,msg->info.name);
	strcpy(user.passwd,msg->passwd);
	user.type = STAFF;
	user.no = msg->info.no;

	while((User_wmark > 0)&&(User_rmark > 0)) //实现读与写和读文件的互斥
	{
		usleep(100000);
	}
	User_wmark++;

	if((fp = fopen("./user.dat","ab")) == NULL)
	{
		printf("User %s requset:open user.dat failed\n",msg->name);
		msg->sign = FAILED;
		strcpy(msg->data,"not file");
		return;
	}

	fwrite(&(user),sizeof(USER),1,fp);//写文件

	printf("add user for %s  ok!\n",msg->name);

	msg->sign = SUCCESS;
	strcpy(msg->data,"add user ok!\n");

	fclose(fp);
	User_wmark--;

}
