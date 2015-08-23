/**
 * tlpi Exercise 20-2
 * author:fanxiangchao
 * cpmare with answer:http://man7.org/tlpi/code/online/dist/signals/ignore_pending_sig.c.html
 **/
#define _GNU_SOURCE
#include <signal.h>
#include "signal_functions.h"
#include "tlpi_hdr.h"


int main(int argc,char* argv[])
{
    int n;
    int sleepSecs;
    sigset_t pendingMask,blockingMask,emptyMask;

    printf("%s: PID is %ld\n",argv[0],(long)getpid());
    for (n = 1; n < NSIG; n++)
    {
        (void)signal(n,SIG_IGN);
    }

    if (argc == 1)
    {
        sleepSecs = 30;
    }
    else
    {
        sleepSecs = getInt(argv[1],GN_GT_0,NULL);
    }

    /*
    sigfillset(&blockingMask);
    if (sigprocmask(SIG_SETMASK,&blockingMask,NULL) == -1)
    {
        errExit("sigprocmask");
    }
    */
    printf("%s: sleeping for %d seconds\n",argv[0],sleepSecs);
    sleep(sleepSecs);
    printf("%s: wakeup ...\n",argv[0]);
    
    if (sigpending(&pendingMask) == -1)
    {
        errExit("sigpending");
    }

    printf("%s: pending signals are: \n",argv[0]);
    printSigset(stdout,"\t\t",&pendingMask);

    sigemptyset(&emptyMask);
    if (sigprocmask(SIG_SETMASK,&emptyMask,NULL) == -1)
    {
        errExit("sigprocmask");
    }

    exit(EXIT_SUCCESS);
}


