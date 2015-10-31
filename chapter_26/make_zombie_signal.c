#include <signal.h>
#include <sys/wait.h>
#include <libgen.h>   /* For basename() declaration */
#include "curr_time.h"
#include "tlpi_hdr.h"

#define CMD_SIZE 200

static void sigHandler(int sig)
{
    int savedErrno;
    savedErrno = errno;
    printf("%s Caught SIGCHLD %d\n",currTime("%T"));
    errno = savedErrno;
}

int main(int argc,char *argv[])
{
    char cmd[CMD_SIZE];
    pid_t childPid;
    sigset_t blockMask,emptyMask;
    struct sigaction sa;

    setbuf(stdout,NULL);    /* Disable buffering of stdout */

    memset(cmd,0,CMD_SIZE);
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigHandler;
    if (sigaction(SIGCHLD,&sa,NULL) == -1)
    {
        errExit("sigaction");
    }

    /* Block SIGCHLD to prevent its delivery if a child terminates
       before the parent commences the sigsupsend() */
    sigemptyset(&blockMask);
    sigaddset(&blockMask,SIGCHLD);
    if (sigprocmask(SIG_SETMASK,&blockMask,NULL) == -1)
    {
        errExit("sigprocmask");
    }
    
    printf("Parent PID=%ld\n",(long)getpid());

    switch(childPid = fork())
    {
    case -1:
        errExit("fork");
    case 0:   /* Child: immediately exits to become zombie */
        printf("Child (PID=%ld) exiting\n",(long)getpid());
        _exit(EXIT_SUCCESS);
    default:  /* Parent */

        sigemptyset(&emptyMask);
        if (sigsuspend(&emptyMask) == -1 && errno != EINTR)
        {
            errExit("sigsuspend");
        }
        
        snprintf(cmd,CMD_SIZE,"ps -c | grep %s",basename(argv[0]));
        cmd[CMD_SIZE - 1] = '\0';   /* Ensure string is null-terminated */
        system(cmd);               /* View zombie child */
        
        /* Now send the "sure kill" signal to the zombie */

        if (kill(childPid,SIGKILL) == -1)
        {
            errMsg("kill");
        }

        sleep(10);   /* Give child a chance to react to signal */
        printf("After sending SIGKILL to zombie (PID=%ld):\n",(long)childPid);
        system(cmd);   /* View zombie child again */
        
        exit(EXIT_SUCCESS);
    }
}
