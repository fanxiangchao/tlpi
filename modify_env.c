/*
 * tlpi Example 6-4 modify environment
 * ./modify_env "GREET=Guten Tag" SHELL=/bin/bash BYE=Ciao
 * ./modify_env SHELL=/bin/sh BYE=byebye
 * author:fanxiangchao
 */

#define _GNU_SOURCE   /* To get various declearations from <stdlib.h> */
#include <stdlib.h>
#include "tlpi_hdr.h"

extern char **environ;

int main(int argc,char *argv[])
{
    int j;
    char **ep;

    clearenv();    /* Erase entire environment */

    for (j = 1; j < argc; j++)
    {
        if (putenv(argv[j]) != 0)
        {
            errExit("putent: %s",argv[j]);
        }
    }

    if (setenv("GREET","Hello world",0) == -1)
    {
        errExit("setenv");
    }

    unsetenv("BYE");

    for (ep = environ; *ep != NULL; ep++)
    {
        puts(*ep);
    }

    exit(EXIT_SUCCESS);
    
}