/**
 * tlpi Example 20-2
 * author:fanxiangchao
 **/

#include <signal.h>
#include "tlpi_hdr.h"

static void sigHandler(int sig)
{
    static int count = 0;

    /* UNSAFE: This handler uses non-async-signal-safe functions
     (printf, exit(); )*/
    if (sig == SIGINT)
    {
        count++;
        printf("Caught SIGINT (%d)\n",count);
        return;   /* Resume execution at point of interruption */
    }

    /* Must be SIGQUIT - print a message and terminate the process */
    printf("Caught SIGQUIT - that's all folks!\n");
    exit(EXIT_SUCCESS);
}

int main(int argc,char *argv[])
{
    if (signal(SIGINT,sigHandler) == SIG_ERR)
    {
        errExit("signal");
    }

    if (signal(SIGQUIT,sigHandler) == SIG_ERR)
    {
        errExit("signal");
    }

    /* Loop forever, waiting for signals */
    for (;;)
    {
        pause(); /* Block until a siganl is caught */
    }
}