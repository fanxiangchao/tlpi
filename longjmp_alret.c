/*
 * tlpi Exercise 6-2
 * jump into already return function
 * ./longjmp_alret & ./longjmp_alret xxx
 * author:fanxiangchao
 */

#include <setjmp.h>
#include "tlpi_hdr.h"

static jmp_buf env;

static void dosetJump()
{
    printf("dosetJump...\n");
    if (setjmp(env) == 0)
    {
        printf("initial setjmp\n");
    }
    else
    {
        printf("jmp here\n");
    }
}

static void doJump()
{
    printf("doJump...\n");
    longjmp(env,1);
}

int main(int argc,char *argv[])
{

    if (argc == 1)
    {
        printf("call dosetJump()\n");
        dosetJump();
    }else
    {
        printf("call doJump()\n");
        doJump();
    }
    
    exit(EXIT_SUCCESS);
}