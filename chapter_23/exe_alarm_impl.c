/* Exercise 23-1
   Implement alarm function by settimer function
 */
#include <sys/time.h>
#include <sys/signal.h>
#include "tlpi_hdr.h"

static void alarmHandler(int sig)
{
    printf("alarm handler caught signal %d\n",sig);
}

unsigned int alarmNew(unsigned int seconds)
{
    struct itimerval itv;
    struct itimerval preItv;
    
    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = seconds;
    itv.it_value.tv_usec = 0;

    if (setitimer(ITIMER_REAL,&itv,&preItv) == -1)
    {
        return 0;
    }

    return preItv.it_value.tv_sec;
}

int main(int argc,char *argv[])
{
    int seconds;
    struct sigaction sa;
    
    if (argc < 2 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s seconds\n",argv[0]);
    }

    seconds = getInt(argv[1],GN_GT_0,"seconds");
    sa.sa_flags = 0;
    sa.sa_handler = alarmHandler;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGALRM,&sa,NULL) == -1)
    {
        errExit("sigaction");
    }
    
    alarmNew(seconds);

    seconds = alarmNew(seconds * 2);
    printf("pre timer left : %d\n",seconds);
    pause();
}