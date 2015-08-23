/*
 * tlpi execise 5-5 5-6
 * author:fanxiangchao
 */
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int fd1,fd2,fd3;
    ssize_t numWrite;
    int flags1,flags2;
    
    if (argc != 2 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s filename\n",argv[0]);
    }

    fd1 = open(argv[1],O_RDWR | O_TRUNC | O_CREAT,S_IRUSR|S_IWUSR);
    if (fd1 == -1)
    {
        errExit("open");
    }

    fd2 =dup(fd1);
    if (fd2 == -1)
    {
        errExit("open");
    }

    fd3 = open(argv[1],O_RDWR);
    if (fd3 == -1)
    {
        errExit("open");
    }

    printf("f1:%d, f2:%d, f3:%d\n",fd1,fd2,fd3);

    numWrite = write(fd1,"Hello,",6);
    if (numWrite == -1)
    {
        errExit("write");
    }

    printf("fd1 offset is %ld,fd2 offset is %ld\n",lseek(fd1,0,SEEK_END),lseek(fd2,0,SEEK_END));

    flags1 = fcntl(fd1,F_GETFL);
    flags2 = fcntl(fd2,F_GETFL);
    printf("fd1 flags %d,fd2 flags %d\n",flags1,flags2);

    write(fd2,"world!",6);
    lseek(fd2,0,SEEK_SET);
    write(fd1,"HELLO,",6);
    write(fd3,"Gidday",6);

    if (close(fd1) == -1)
    {
        errExit("close");
    }

    if (close(fd2) == -1)
    {
        errExit("close");
    }

    if (close(fd3) == -1)
    {
        errExit("close");
    }

    exit(EXIT_SUCCESS);
        
}
