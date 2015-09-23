#include "tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int childPid;

    switch((childPid = vfork()))
    {
    case -1:
        errExit("vfork");
    case 0:
        printf("Child ready to close stdout stream\n");
        if (close(STDOUT_FILENO) == -1)
        {
            errExit("close");
        }

        _exit(EXIT_SUCCESS);
    default:
        printf("Parent ready to write something to stdou stream\n");
        write(STDOUT_FILENO,"hello world\n",12);
        exit(EXIT_SUCCESS);
    }
}