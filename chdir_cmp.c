/**
 * tlpi Exercier 18-9
 * author:fanxiangchao
 **/
#define _XOPEN_SOURCE 500  /* Or: #define _BSD_SOURCE */
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include "tlpi_hdr.h"

#define BUF_SIZE PATH_MAX

int main(int argc,char *argv[])
{
    time_t start;
    time_t end;
    int fd;
    char buf[BUF_SIZE];
    int i;
    struct timeval stval;
    struct timeval enval;
    
    if (argc < 2 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("Usage: %s filedir\n",argv[0]);
    }

    realpath(".",buf);
    
    start = time(NULL);
    gettimeofday(&stval,NULL);
    for (i = 0; i < 10000000; i++)
    {
        chdir(argv[1]);
        chdir(buf);
    }
    end = time(NULL);
    gettimeofday(&enval,NULL);

    printf("chdir time: %d, %d\n",(end - start),(enval.tv_sec * 1000 + enval.tv_usec -
                                                 stval.tv_sec * 1000 + stval.tv_usec));
    fd = open(".",O_RDONLY);
    start = time(NULL);
    gettimeofday(&stval,NULL);
    for (i = 0; i < 10000000; i++)
    {
        chdir(argv[1]);
        fchdir(fd);
    }
    end = time(NULL);
    gettimeofday(&enval,NULL);
    
    close(fd);

    printf("fchdir time: %d, %d\n",(end - start),(enval.tv_sec * 1000 + enval.tv_usec -
                                                 stval.tv_sec * 1000 + stval.tv_usec));
    // printf("fchdir time: %d\n",(end - start));
}