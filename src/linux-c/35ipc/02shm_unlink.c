#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define ERR_EXIT(m) \
        do \
        { \
                perror(m); \
                exit(EXIT_FAILURE); \
        } while(0)

typedef struct stu
{
	char name[32];
	int age;
} STU;

int main(void)
{
	shm_unlink("/xyz");
	return 0;
}
