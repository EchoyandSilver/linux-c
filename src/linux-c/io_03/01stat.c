#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do \
	{  \
		perror(m); \
		exit(EXIT_FAILURE);\
	}while(0) 

#define MAJOR(a) (int)((unsigned short)a >> 8)
#define MINOR(a) (int)((unsigned short)a & 0xFF)

int filetype(struct stat *buf);
void fileperm(struct stat *buf,char *perm);

int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr,"Usage %s file\n",argv[0]);
		exit(EXIT_FAILURE);
	}	
	
	struct stat sbuf;
	printf("File name:%s\n",argv[1]);
	if(lstat(argv[1], &sbuf) == -1)
		ERR_EXIT("stat error");

	printf("File number: MAJOR(%d),MINOR(%d),inode(%d)\n",MAJOR(sbuf.st_dev)		,MINOR(sbuf.st_dev),(int)sbuf.st_ino);
	
	if(filetype(&sbuf))
	{
		printf("Device number: MAJOR(%d),MINOR(%d)\n",MAJOR(sbuf.st_rdev)
		,MINOR(sbuf.st_rdev));
	}	
	
	char perm[11] = {0};
	fileperm(&sbuf,perm);
	printf("File permission bit= %o %s\n",sbuf.st_mode & 07777, perm);

	return 0;
}

int filetype(struct stat *buf)
{
	int flag;
	printf("Filetype:");
	mode_t mode;
	mode = buf->st_mode;
	switch(mode & S_IFMT)
	{
		case S_IFSOCK:
			printf("socket\n");
			break;
		case S_IFLNK:
			printf("symbolic link\n");
			break;
		case S_IFREG:
			printf("regular file\n");
			break;
		case S_IFBLK:
			printf("block device\n");
			flag = 1;
			break;
		case S_IFDIR:
			printf("directory\n");
			break;
		case S_IFCHR:
			printf("character\n");
			flag = 1;
			break;
		case S_IFIFO:
			printf("FIFO\n");
			break;
		default:
			printf("unknow\n");
	}
	
	return flag;
}	

void fileperm(struct stat *buf,char *perm)
{
	strcpy(perm,"----------");
	perm[0] = '?';
	mode_t mode;
        mode = buf->st_mode;
        switch(mode & S_IFMT)
        {
                case S_IFSOCK:
                	perm[0] = 's';
		        break;
                case S_IFLNK:
			perm[0] = 'l';;	
                case S_IFREG:
                	perm[0] = '-';
                        break;
                case S_IFBLK:
                	perm[0] = 'b';
                        break;
                case S_IFDIR:
                	perm[0] = 'd';
                        break;
                case S_IFCHR:
                	perm[0] = 'c';
                        break;
                case S_IFIFO:
                	perm[0] = 'p';
                        break;
        }
	
	if(mode & S_IRUSR)
		perm[1] = 'r';
	if(mode & S_IWUSR)
		perm[2] = 'w';
	if(mode & S_IXUSR)
		perm[3] = 'x';
	if(mode & S_IRGRP)
		perm[4] = 'r';
	if(mode & S_IWGRP)
		perm[5] = 'x';
	if(mode & S_IXGRP)
		perm[6] = 'x';
	if(mode & S_IROTH)
		perm[7] = 'r';
	if(mode & S_IWOTH)
		perm[8] = 'w';
	if(mode & S_IXOTH)
		perm[9] = 'x';
	perm[10] = '\0';
}
