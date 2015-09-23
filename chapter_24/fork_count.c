#include "tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int childPid;
    int i;

    for (i = 0;i < 3; i++)
    {
        if ((childPid = fork()) == -1)
        {
            errExit("fork");
        }else if (childPid == 0)
        {
            printf("child : %ld, parent : %ld\n",getpid(),getppid());
        }else
        {
            /*printf("parent\n");*/
            wait(NULL);
        }
    }
    
    exit(EXIT_SUCCESS);

}