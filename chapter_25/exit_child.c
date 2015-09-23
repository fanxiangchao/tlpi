#include <sys/wait.h>
#include <sys/types.h>
#include "tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int childPid;
    int stat;
    
    switch((childPid = fork()))
    {
    case -1:
        errExit("fork");
    case 0:
        printf("child ...\n");
        sleep(2);
        exit(-1);
    default:
         wait(&stat);
         printf("stat from child %d is %d, WIFEXITED=%d\n",childPid,WEXITSTATUS(stat),WIFEXITED(stat));
         exit(EXIT_SUCCESS);
    }
}
