#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <signal.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

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

mqd_t mqid;
size_t size;
struct sigevent sigev;

void handle_sigusr1(int sig)
{
	mq_notify(mqid, &sigev);
        STU stu;

        unsigned prio;
        if (mq_receive(mqid, (char*)&stu, size, &prio) == (mqd_t)-1)
                ERR_EXIT("mq_receive");

        printf("name=%s age=%d prio=%u\n", stu.name, stu.age, prio);

}

int main(int argc, char *argv[])
{
	mqid = mq_open("/abc", O_RDONLY);
	if (mqid == (mqd_t)-1)
		ERR_EXIT("mq_open");	

	struct mq_attr attr;
        mq_getattr(mqid, &attr);
	size = attr.mq_msgsize;

	signal(SIGUSR1, handle_sigusr1);

	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGUSR1;

	mq_notify(mqid, &sigev);
	
	for (;;)
		pause();

	mq_close(mqid);
	return 0;
}
