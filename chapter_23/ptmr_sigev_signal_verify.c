#define _POSIX_C_SOURCE 199309
#include <signal.h>
#include <time.h>
#include "curr_time.h"   /* Declares currTime() */
#include "itimerspec_from_str.h" /* Declares itimerspecFromStr()*/
#include "tlpi_hdr.h"

#define TIMER_SIG SIGRTMAX   /* Our timer notification signal */

static void handler(int sig,siginfo_t *si,void *uc)
{
    int tid;

    tid = si->si_value.sival_int;

    /* UNSAFE: This handler uses non-async-signal-safe functions
       (printf();)*/
    printf("[%s] Got signal %d\n",currTime("%T"),sig);
    printf("     sival_int         = %ld\n",(long)tid);
    
}

int main(int argc,char *argv[])
{
    struct itimerspec ts;
    struct sigaction sa;
    timer_t *tidlist;
    int j;

    if (argc < 2)
    {
        usageErr("%s secs[/nsecs][:int-secs[/int-nsecs]]...\n",argv[0]);
    }

    tidlist = calloc(argc - 1,sizeof(timer_t));
    if (tidlist == NULL)
    {
        errExit("malloc");
    }

    /* Establish handler for notification signal */
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGALRM,&sa,NULL) == -1)
    {
        errExit("sigaction");
    }
    
    for (j = 0; j < argc - 1; j++)
    {
        itimerspecFromStr(argv[j + 1],&ts);
        /* Allows handler to get ID of  this timer */

        if (timer_create(CLOCK_REALTIME,NULL,&tidlist[j]) == -1)
        {
            errExit("timer_create");
        }

        printf("Timer ID: %ld (%s)\n",(long)tidlist[j],argv[j + 1]);

        if (timer_settime(tidlist[j],0,&ts,NULL) == -1)
        {
            errExit("timer_settime");
        }
    }

    for (;;)          /* Wait for incoming timer signals */
    {
        pause();
    }
}