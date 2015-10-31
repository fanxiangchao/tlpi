#include "tlpi_hdr.h"

int main(int argc,char *argv[])
{
    switch(fork())
    {
    case -1:
        errExit("fork");
    case 0:    /* Child,sleep give parent a chance to exit  */
        printf("Child %ld, Parent %ld\n",(long)getpid(),(long)getppid());
        sleep(5);
        printf("Child %ld, Parent %ld\n",(long)getpid(),(long)getppid());
        _exit(EXIT_SUCCESS);
    default:
        printf("Parent %ld\n",(long)getpid());
        sleep(3);
        printf("Parent exit.\n");
        exit(EXIT_SUCCESS);
    }
}