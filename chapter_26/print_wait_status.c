#define _GNU_SOURCE   /* Get strsignal() declartion from <string.h> */
#include <string.h>
#include <sys/wait.h>
#include "print_wait_status.h"   /* Declaration of printWaitStatus() */
#include "tlpi_hdr.h"

/* NOTE: The following function employs printf(),which is not
   async-signal-safe(see Section 21.1.2). As such,this function is
   also not async-signal-safe (i.e.,beware of calling it from SIGCHILD handler).*/

void                  /* Examine a wait() status using the W* macros */
printWaitStatus(const char *msg,int status)
{
    if (msg != NULL)
    {
        printf("%s",msg);
    }

    if (WIFEXITED(status))
    {
        printf("child exited, status=%d\n",WEXITSTATUS(status));
    }else if (WIFSIGNALED(status))
    {
        printf("child killed by signal %d (%s)",
               WTERMSIG(status),strsignal(WTERMSIG(status)));
#ifdef WCOREDUMP    /* Not in SUSv3, may be absent on some systems */
        if (WCOREDUMP(status))
        {
            printf(" (core dumped)");
#endif
            printf("\n");
        }
    }else if (WIFSTOPPED(status))
    {
        printf("child stopped by signal %d (%s)\n",
               WSTOPSIG(status),strsignal(WSTOPSIG(status)));
#ifdef WIFCONTINUED  /* SUSv3 has this,but older Linux versions and
                       some other UNIX implementations don't */
    }else if (WIFCONTINUED(status))
    {
        printf("child continued\n");
#endif
    }else   /* Should never happen */
    {
        printf("what happened to this child? (status=%x)\n",
               (unsigned int)status);
    }

}

void printWaitIdSigInfo(const siginfo_t *infop)
{
    if (infop == NULL)
    {
        printf("NULL siginfo.\n");
        return;
    }

    printf("child(%ld) ",infop->si_pid);
    if (infop->si_code == CLD_EXITED)
    {
        printf("exit, ");
    }else if (infop->si_code == CLD_KILLED)
    {
        printf("killed, ");
    }else if (infop->si_code == CLD_STOPPED)
    {
        printf("stopped, ");
    }else if (infop->si_code == CLD_CONTINUED)
    {
        printf("continued, ");
    }else
    {
        printf("unknow status, what happened to this child, ");
    }

    printf("status=%x\n",(unsigned int)infop->si_status);
}