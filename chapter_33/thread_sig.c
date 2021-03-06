#include <pthread.h>
#include <signal.h>
#include "signal_functions.h"
#include "tlpi_hdr.h"

static void *threadFunc1(void *arg)
{
    sigset_t blockMask;
    sigset_t originMask;

    sigemptyset(&blockMask);
    sigaddset(&blockMask,SIGUSR1);
    if (pthread_sigmask(SIG_BLOCK,&blockMask,&originMask) == -1)
    {
        errExit("sigprocmask");
    }

    printf("threadFunc1: waiting for %d signal\n",SIGUSR1);
    sleep(5);
    printPendingSigs(stdout,"threadFunc1: ");

    if (pthread_sigmask(SIG_BLOCK,&originMask,NULL) == -1)
    {
        errExit("sigprocmask");
    }

    return NULL;
}

static void *threadFunc2(void *arg)
{
    sigset_t blockMask;
    sigset_t originMask;

    sigemptyset(&blockMask);
    sigaddset(&blockMask,SIGUSR2);
    if (pthread_sigmask(SIG_BLOCK,&blockMask,&originMask) == -1)
    {
        errExit("sigprocmask");
    }

    printf("threadfunc2: waiting for %d signal\n",SIGUSR2);
    sleep(5);
    printPendingSigs(stdout,"threadFunc2: ");

    if (pthread_sigmask(SIG_BLOCK,&originMask,NULL) == -1)
    {
        errExit("sigprocmask");
    }

    return NULL;

}

int main(int argc,char *argv[])
{
    pthread_t t1,t2;
    int s;
    
    s = pthread_create(&t1,NULL,threadFunc1,NULL);
    if (s != 0)
    {
        errExitEN(s,"pthread_create");
    }

    s = pthread_create(&t2,NULL,threadFunc2,NULL);
    if (s != 0)
    {
        errExitEN(s,"pthread_create");
    }

    sleep(2);
    
    s = pthread_kill(t1,SIGUSR1);
    if (s != 0)
    {
        errExitEN(s,"pthread_kill");
    }
    
    s = pthread_kill(t2,SIGUSR2);
    if (s != 0)
    {
        errExitEN(s,"pthread_kill");
    }
    
    s = pthread_join(t1,NULL);
    if (s != 0)
    {
        errExitEN(s,"pthread_join");
    }

    s = pthread_join(t2,NULL);
    if (s != 0)
    {
        errExitEN(s,"pthread_join");
    }

    exit(EXIT_SUCCESS);
    
}