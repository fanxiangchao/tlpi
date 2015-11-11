#include <sys/wait.h>
#include "tlpi_hdr.h"

#define CALL_FORK_NUM 100000

int main(int argc,char *argv[])
{
    pid_t childPid;
    pid_t (*t_fork)();
    int i;
    
    if (argc < 2 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s [fork|vfork]\n",argv[0]);
    }

    if (strcmp(argv[1],"fork") == 0)
    {
        t_fork = fork;
    }else if (strcmp(argv[1],"vfork") == 0)
    {
        t_fork = vfork;
    }else
    {
        printf("invalid option,input fork or vfork");
        usageErr("%s [fork|vfork]\n",argv[0]);
    }

    for (i = 0;i < CALL_FORK_NUM; i++)
    {
        switch((childPid = t_fork()))
        {
        case -1:
            errExit("fork|vfork");
        case 0:
            _exit(EXIT_SUCCESS);
        default:
            if (waitpid(-1,NULL,0) == -1)
            {
                errExit("waitpid()");
            }
        }
    }
    
    exit(EXIT_SUCCESS);
}