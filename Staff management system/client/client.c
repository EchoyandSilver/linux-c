#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "client.h"


int main(int argc, const char *argv[])
{
	int sockfd;
	struct sockaddr_in  serveraddr;
	MSG  msg;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		exit(1);
	}

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
	{
		perror("connect");
		exit(1);
	}

	while(1)
	{
		puts("------------------------------------");
		puts("----------Login ^_^  ^_^-------------");
		puts("------------------------------------");

		/*
		 *  输入登录信息
		 */
		printf("please input your name >");
		fgets(msg.name, N, stdin);
		msg.name[strlen(msg.name) - 1] = '\0';

		printf("please input your password >");
		fgets(msg.passwd, N, stdin);
		msg.passwd[strlen(msg.passwd) - 1] = '\0';
		msg.type = LOAD;


		send(sockfd, &msg, sizeof(MSG), 0);//发送消息给服务器，进行登录验证。
		printf("---load type %d\n", msg.type);
		recv(sockfd, &msg, sizeof(MSG), 0);//接收服务器的反馈消息。

		if(msg.sign ==  FAILED)//登录失败
		{
			printf("%s\n", msg.data);
			continue;
		}

		if(msg.sign == SUCCESS)//登录成功 
		{
			if(msg.info.type == STAFF)
			{
				goto User;//进入普通用户界面
			}
			else if(msg.info.type == ADM)
			{
				goto Admin;// 进入管理员界面 
			}
		}
	}

	/*普通用户界面*/
User:
	while(1)
	{
		/*普通用户权限*/
		puts("----------------------------------------------------");
		puts("-------1: select info 2:modify passwd 3:exit --------");
		puts("-----------------------------------------------------");
		printf("please input you command >");

		/*
		 *输入命令错误处理
		 */
		int command;
		char clear[N];
		if(scanf("%d",&command) == 0)
		{
			fgets(clear, N, stdin);
			continue;
		}

		switch(command)
		{
		case 1:
			msg.type = READ;
			strcpy(msg.info.name , msg.name); 
			msg.info.no = 0;

			send(sockfd, &msg, sizeof(MSG), 0);//发送查询消息
			recv(sockfd, &msg, sizeof(MSG), 0);//接收服务器的反馈消息
			printf(" ---------recv sign %d\n", msg.sign);
			/*打印用户自身信息*/

			printf("姓名    地址                  年龄    级别\n");
			printf("%s %s %d %d \n",msg.info.name, msg.info.addr, msg.info.age, msg.info.level);
			printf("编号    工资    电话      用户类型\n");
			printf("%d %lf %s %d \n",msg.info.no, msg.info.salary, msg.info.phone, msg.info.type);

			break;
		case 2:
			getchar();
			printf("please input your new password >");
			getchar();
			fgets(msg.passwd, N, stdin);
			msg.passwd[strlen(msg.passwd) - 1] = '\0'; 
			msg.type = CHANGE;
			send(sockfd, &msg, sizeof(MSG), 0);//发送修改密码的消息
			break;

		case 3:
			msg.type = QUIT;
			send(sockfd, &msg, sizeof(MSG), 0);
			goto Exit;//退出程序
		}
	}


/*管理员界面*/
Admin:
	while(1)
	{
		/*管理员的权限*/
		puts("--------------------------------------------------------------------");
		puts("-----1:add user 2:delete user  3:modify info 4:select info  5:exit ----");
		puts("---------------------------------------------------------------------");
		printf("please input you command >");//输入对应的操作数字。

		/*输入命令错误处理*/
		int result;
		int command;
		char clear[N];
		if(scanf("%d",&command) == 0)
		{
			fgets(clear, N, stdin);
			continue;
		}

		switch(command)
		{
		case 1:

			/*添加用户*/
			do_adduser(sockfd, &msg);
			if(result == SUCCESS)
			{
				puts("register OK");
			}
			else if(result == FAILED)
			{
				printf("%s\n", msg.data);
				continue;
			}
			break;

		case 2:
			/*删除用户*/
			result = do_deluser(sockfd, &msg);
			if(result == SUCCESS)
			{
				puts("delete OK!");
			}
			else if(result == FAILED)
			{
				printf("%s\n", msg.data);
				puts("failed to delete user");
				continue;
			}
			break;

		case 3:
			/*修改用户信息*/
			result = do_modifyuser(sockfd, &msg);
			if(result == SUCCESS)
			{
				puts("success to modify !");
			}
			else if(result == FAILED)
			{
				printf("%s\n", msg.data);
				puts("failed to modify!");
				continue;
			}
			break;
		case 4:	
			/*查询用户信息*/
			result = do_selectuser( sockfd, &msg);
			if( result == SUCCESS)
			{
				printf("姓名    地址                  年龄    级别\n");
				printf("%s %s %d %d \n",msg.info.name, msg.info.addr, msg.info.age, msg.info.level);
				printf("编号    工资    电话      用户类型\n");
				printf("%d %lf %s %d \n",msg.info.no, msg.info.salary, msg.info.phone, msg.info.type);
			}
			else if( result == FAILED)
			{
				printf("%s\n", msg.data);
				puts("failed to select!");
				continue;
			}
			break;
		case 5:
			msg.type = QUIT;
			send(sockfd, &msg, sizeof(MSG), 0);
			goto Exit;
		}
	}

Exit:
	close(sockfd); //退出时关闭套接字
	return 0;
}


/*添加用户*/
int do_adduser(int sockfd, MSG *msg)
{
	printf("please input username >");
	getchar();//清除垃圾字符
	fgets((msg->info).name, N, stdin);
	(msg->info).name[strlen((msg->info).name) - 1] = '\0'; 

	printf("please input userpasswd >");
	fgets(msg->passwd, N, stdin);
	msg->passwd[strlen(msg->passwd) - 1] = '\0'; 

	printf("please input useraddr >");
	fgets((msg->info).addr, N, stdin);
	(msg->info).addr[strlen((msg->info).addr) - 1] = '\0'; 

	char clear[N];
input_age: 
	printf("please input userage >"); //输入类型不匹配时重新输入
	if(scanf("%d",&(msg->info.age)) == 0)
	{
		printf("the type error!\n");
		fgets(clear, N, stdin);//清理输入垃圾
		goto input_age;
	}
	getchar();

input_level:
	printf("please input userlevel >");
	if(scanf("%d",&(msg->info.level)) == 0)
	{
		printf("the type error!\n");
		fgets(clear, N, stdin);
		goto input_level;
	}
	getchar();

input_usrno:
	printf("please input userno >");
	if(scanf("%d",&(msg->info.no)) == 0)
	{
		printf("the type error!\n");
		fgets(clear, N, stdin);
		goto input_usrno;
	}
	getchar();

input_salary:
	printf("please input usersalary >");
	if(scanf("%lf",&(msg->info.salary)) == 0)
	{
		printf("the type error!\n");
		fgets(clear, N, stdin);
		goto input_salary;
	}
	getchar();

	printf("please input userphone >");
	fgets((msg->info).phone, N, stdin);
	(msg->info).phone[strlen((msg->info).phone) - 1 ] = '\0';

input_usertype:
	printf("please input usertype >");
	if(scanf("%d", &(msg->info.type)) == 0)
	{
		printf("the type error!\n");
		fgets(clear, N, stdin);
		goto input_usertype;
	}
	getchar();

	msg->type = ADD;//发送个服务器的操作类型

	/*
	 * 发送给服务器的结构体类型
	 * 必须和客户端的一致。
	 */
	send(sockfd, msg, sizeof(MSG), 0);
	recv(sockfd, msg, sizeof(MSG), 0);

	return msg->sign;// 返回服务器端的处理信息。

}

/*删除用户*/
int do_deluser(int sockfd, MSG *msg)
{
	printf("please input username >");
	getchar();
	fgets((msg->info).name, N, stdin);
	(msg->info).name[strlen((msg->info).name) - 1] = '\0'; 

	printf("please input userno >");
	if(scanf("%d", &(msg->info.no)) == 0)
	{
		msg->info.no = 0;
	}

	msg->type =  DELETE;
	send(sockfd, msg, sizeof(MSG) , 0);
	recv(sockfd, msg, sizeof(MSG) , 0);

	return msg->sign;// 返回服务器端的处理信息。
}

/*查询用户信息*/
int do_selectuser(int sockfd, MSG *msg)
{
	printf("please input username >");
	getchar();
	fgets((msg->info).name, N, stdin);
	(msg->info).name[strlen((msg->info).name) - 1] = '\0'; 

	/*
	 * 当输入其他字符时，默认要查询的no的值为0。
	 */
	printf("please input userno >");
	if(scanf("%d", &(msg->info.no)) == 0)
	{
		msg->info.no = 0;
	}
	msg->type =  READ;//发送给服务器的操作类型。 
	send(sockfd, msg, sizeof(MSG) , 0);
	recv(sockfd, msg, sizeof(MSG) , 0);

	return msg->sign;// 返回服务器端的处理信息。
}

/*修改用户信息*/
int do_modifyuser(int sockfd, MSG *msg)
{
	printf("please input username >");
	getchar();
	fgets((msg->info).name, N, stdin);
	(msg->info).name[strlen((msg->info).name) - 1] = '\0'; 

	printf("please input userpasswd >");
	fgets(msg->passwd, N, stdin);
	msg->passwd[strlen(msg->passwd) - 1] = '\0'; 

	printf("please input useraddr >");
	fgets((msg->info).addr, N, stdin);
	(msg->info).addr[strlen((msg->info).addr) - 1] = '\0'; 

	char clear[N];
input_age: 
	printf("please input userage >");
	if(scanf("%d",&(msg->info.age)) == 0)
	{
		printf("the type error!\n");
		fgets(clear, N, stdin);
		goto input_age;
	}
	getchar();

input_level:
	printf("please input userlevel >");
	if(scanf("%d",&(msg->info.level)) == 0)
	{
		printf("the type error!\n");
		fgets(clear, N, stdin);
		goto input_level;
	}
	getchar();

input_usrno:
	printf("please input userno >");
	if(scanf("%d",&(msg->info.no)) == 0)
	{
		printf("the type error!\n");
		fgets(clear, N, stdin);
		goto input_usrno;
	}
	getchar();

input_salary:
	printf("please input usersalary >");
	if(scanf("%lf",&(msg->info.salary)) == 0)
	{
		printf("the type error!\n");
		fgets(clear, N, stdin);
		goto input_salary;
	}
	getchar();

	printf("please input userphone >");
	fgets((msg->info).phone, N, stdin);
	(msg->info).phone[strlen((msg->info).phone) - 1 ] = '\0';

input_usertype:
	printf("please input usertype >");
	if(scanf("%d", &(msg->info.type)) == 0)
	{
		printf("the type error!\n");
		fgets(clear, N, stdin);
		goto input_usertype;
	}
	getchar();

	msg->type = CHANGE;
	send(sockfd, msg, sizeof(MSG), 0);
	recv(sockfd, msg, sizeof(MSG), 0);

	return msg->sign;// 返回服务器端的处理信息。
}



