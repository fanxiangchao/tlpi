#include <stdio.h>
#include <signal.h>
#include "tlpi_hdr.h"

void sigHandler(int sig)
{
    printf("Caught signal %d\n",sig);
}

int main(int argc,char *argv[])
{
    pid_t childPid;
    sigset_t blockMask,origMask;
    struct sigaction sa;

    sa.sa_flags = 0;
    sa.sa_handler = sigHandler;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGCHLD,&sa,NULL) == -1)
    {
        errExit("sigaction");
    }

    sigaddset(&blockMask,SIGCHLD);
    if (sigprocmask(SIG_BLOCK,&blockMask,&origMask) == -1)
    {
        errExit("sigaction");
    }

    switch((childPid = fork()))
    {
    case -1:
        errExit("fork");
    case 0:   /* Children */
        /* Do somthing */
        sleep(2);
        _exit(EXIT_SUCCESS);
    default: /* Parent */
        if (wait(NULL) == -1)
        {
            errExit("wait");
        }

        if (sigprocmask(SIG_SETMASK,&origMask,NULL) == -1)
        {
            errExit("sigprocmask");
        }
    }

    exit(EXIT_SUCCESS);
}
