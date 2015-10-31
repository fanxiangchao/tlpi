#include "tlpi_hdr.h"

int main(int argc,char *argv[])
{
    pid_t sonPid;
    pid_t grandSonPid;
    
    switch(fork())
    {
    case -1:
        errExit("fork");
    case 0:   /* Son */
        if ((grandSonPid = fork()) == -1)
        {
            errExit("fork");
        }else if (grandSonPid == 0)  /* Grandson */
        {
            printf("Grandson %ld sleep,it's parent is %ld ...\n",(long)getpid(),(long)getppid());
            sleep(5);
            printf("Grandson %ld wakeup,it's parent is %ld ...\n",(long)getpid(),(long)getppid());
            sleep(8);
            printf("Grandson %ld,it's parent is %ld ...\n",(long)getpid(),(long)getppid());
        }else
        {
            printf("Son %ld sleep,it's parent is %ld,it's son is %ld ...\n",(long)getpid(),(long)getppid(),(long)grandSonPid);
            sleep(2);
            printf("Son %ld exit\n",(long)getpid());
        }

        _exit(EXIT_SUCCESS);
    default:  /* Grandparent */
        printf("Grandparent %ld sleep ...\n",(long)getpid());
        sleep(10);
        if ((sonPid = wait(NULL)) == -1)
        {
            errExit("wait");
        }
        printf("Grandparent %ld wait son %ld exit\n",(long)getpid(),(long)sonPid);
        exit(EXIT_SUCCESS);
    }
}