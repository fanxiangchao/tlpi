 #include <sys/wait.h>
#include "print_wait_status.h"   /* Declares printWatiStatus() */
#include "tlpi_hdr.h"

int main(int argc,char *argv[])
{
    siginfo_t info;
    pid_t childPid;

    if (argc > 1 && strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s [exit-status]\n",argv[0]);
    }

    switch(fork())
    {
    case -1:
        errExit("fork");
    case 0:   /* Child: either exits immediately with given
                 status or loops waiting for signals */
        printf("Child started with PID = %ld\n",(long)getpid());
        if (argc > 1)   /* Status supplied on command line? */
        {
            exit(getInt(argv[1],0,"exit-status"));
        }
        else           /* Otherwise,wait for signals */
        {
            for(;;)
            {
                pause();
            }

            exit(EXIT_FAILURE);   /* Not reached, but good practice */
        }
    default:   /* Parent: repeatedly wait on child until it
                 either exits or is terminated by a signal */
        for (;;)
        {
            if ( waitid(P_ALL,0,&info,WEXITED | WSTOPPED
#ifdef WCONTINUED   /* Not present on older versions of Linux */
                | WCONTINUED
#endif
                     ))
            {
                errExit("waitpid");
            }

            /* Print status in hex, and as separate decimal bytes */
            printf("waitid() returned: PID=%ld; status=0x%04x (%d,%d)\n",
                   (long)info.si_pid,
                   (unsigned int)info.si_status,
                   info.si_status >> 8,info.si_status & 0xff);

            printWaitIdSigInfo(&info);

            if (info.si_code == CLD_EXITED || info.si_code == CLD_KILLED)
            {
                exit(EXIT_SUCCESS);
            }
                                           
        }
        
    }
}