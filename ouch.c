/**
 * tlpi Example 20-1
 * author:fanxiangchao
 **/

#include <signal.h>
#include "tlpi_hdr.h"

static void sigHandler(int sig)
{
    printf("Ouch!\n");   /* UNSAFE */
}

int main(int argc,char *argv[])
{
    int j;
    if (signal(SIGINT,sigHandler) == SIG_ERR)
    {
        errExit("signal");
    }

    for (j = 0; ; j++)
    {
        printf("%d\n",j);
        sleep(3);  /* Loop slowly ...*/
    }
}