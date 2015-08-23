/**
 * tlpi Exercise 20-4
 * author:fanxiangchao
 * compare with http://man7.org/tlpi/code/online/dist/signals/siginterrupt.c.html
 **/
#include <signal.h>
#include "tlpi_hdr.h"

void handler(int sig)
{
    printf("sig = %d\n",sig);
}

int sigactionInterupt(int sig,int flag)
{
    struct sigaction sa;

    if (sigaction(sig,NULL,&sa) == -1)
    {
        return -1;
    }
    
    if (flag == 0)
    {
        sa.sa_flags |= SA_RESTART;
    }
    else
    {
        sa.sa_flags = (sa.sa_flags & ~SA_RESTART);
    }

    return sigaction(sig,&sa,NULL);
}

int main(int argc,char *argv[])
{

    struct sigaction sa;

    if (sigaction(SIGINT,NULL,&sa) == -1)
    {
        errExit("sigaction");
    }

    sa.sa_handler = handler;
    if (sigaction(SIGINT,&sa,NULL) == -1)
    {
        errExit("sigaction");
    }
    
    printf("interrupt system call,signal = %d\n",SIGINT);
    if (sigactionInterupt(SIGINT,1) == -1)
    {
        errExit("sigactionInterrupt");
    }

    sleep(5);

    printf("restart system call,signal = %d\n",SIGINT);
    if (sigactionInterupt(SIGINT,0) == -1)
    {
        errExit("sigactionInterrupt");
    }

    sleep(15);

    printf("finish !!!\n");

    exit(EXIT_SUCCESS);
    
}