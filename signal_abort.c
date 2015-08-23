/**
 * tlpi Exercise 21-1
 * author:fanxiangchao
 **/
#define _GNU_SOURCE
#include <signal.h>
#include <string.h>
#include "tlpi_hdr.h"

static void handler(int sig)
{
    printf("Caught signal %d(%s)\n",sig,strsignal(sig));
}

void sig_abort()
{
    struct sigaction sa;

    if (sigaction(SIGABRT,NULL,&sa) == -1)
    {
        errExit("sigaction");
    }

    if (sa.sa_handler != SIG_DFL)
    {
        sa.sa_flags |= SA_RESETHAND;
        if (sigaction(SIGABRT,&sa,NULL) == -1)
        {
            errExit("sigaction");
        }

        if (raise(SIGABRT) == -1)
        {
            errExit("raise");
        }
    }

    if (raise(SIGABRT) == -1)
    {
        errExit("raise");
    }
}

int main(int argc,char *argv[])
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGABRT,&sa,NULL) == -1)
    {
        errExit("sigaction");
    }

    abort();

    for (;;)
    {
        pause();
    }
}