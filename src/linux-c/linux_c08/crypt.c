#define _XOPEN_SOURCE
#include <unistd.h> 
#include <string.h>
#include <crypt.h>

int main()
{
	//将密码或数据编码
	char passwd[13];
	char * key;
	char salt[2];
	key = getpass("Input First Password:");
	salt[0] = key[0];
	salt[1] = key[1];	
	strcpy(passwd,crypt(key,salt));
	key = getpass("Input Second Password:");
	salt[0] = passwd[0];
	salt[1] = passwd[1];
	printf("After crypt(),1st passwd:%s\n",passwd);
	printf("After crypt(),2nd passwd:%s\n",crypt(key,salt));
}
