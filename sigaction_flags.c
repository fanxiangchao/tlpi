/**
 * tlpi Exercise 20-3
 * author:fanxiangchao
 * Check SA_RESETHAND and SA_NODEFER
 **/
#include <signal.h>
#include "signal_functions.h"
#include "tlpi_hdr.h"

void handler(int sig)
{
    printf("handler signal = %d\n",sig);
}

void handlerMask(int sig)
{
    struct sigaction sa;
    if (sigaction(SIGINT,NULL,&sa) == -1)
    {
        errExit("sigaction");
    }

    if (sigismember(&sa.sa_mask,SIGINT) == 0)
    {
        printf("not set sig mask %d\n",SIGINT);
    }
}

int main(int argc,char *argv[])
{
    struct sigaction sa;
    sigset_t samask;
    int secs = 10;
    
    sigemptyset(&samask);
    sa.sa_handler = handler;
    sa.sa_mask = samask;
    sa.sa_flags = SA_RESETHAND;

    if (sigaction(SIGINT,&sa,NULL) == -1)
    {
        errExit("sigaction");
    }

    printf("%s: sleep %d\n",argv[0],secs);
    sleep(secs);
    sigaction(SIGINT,NULL,&sa);
    if (sa.sa_handler == SIG_DFL)
    {
        printf("signal handler reset\n");
        printf("%s: sleep %d\n",argv[0],secs);
    }

    sa.sa_handler = handlerMask;
    sa.sa_mask = samask;
    sa.sa_flags = SA_NODEFER;

    if (sigaction(SIGINT,&sa,NULL) == -1)
    {
        errExit("sigaction");
    }

    printf("%s: sleep %d\n",argv[0],secs);
    sleep(secs);

    exit(EXIT_SUCCESS);
    
}

