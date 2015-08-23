/*
 * tlpi execise 5-4
 * author:fanxiangchao
 */

#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int dup_new(int oldfd)
{
    return fcntl(oldfd,F_DUPFD,0);
}

int dup2_new(int oldfd,int newfd)
{
    int flags = fcntl(oldfd,F_GETFL);
    if (flags == -1)
    {
        errno = EBADF;
        return -1;
    }

    /* euqal do nothing */
    if (oldfd == newfd)
    {
        return newfd;
    }

    flags = fcntl(newfd,F_GETFL);
    if (flags != -1)
    {
        close(newfd);
    }
    return fcntl(oldfd,F_DUPFD,newfd);
    
}

int main(int argc,char *argv[])
{
    int fd;

    if (argc != 2 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s filename\n",argv[0]);
    }

    fd = open(argv[1],O_RDONLY);
    if (fd == -1)
    {
        errExit("open");
    }

    printf("%s file description is %d\n",argv[1],fd);
    printf("call dup_new of %s file,new file description is %d\n",argv[1],dup_new(fd));
    printf("call dup2_new of %s file,new file description is %d\n",argv[1],dup2_new(fd,fd));
    printf("call dup2_new of invalid file,new file description is %d,errno is %d\n",dup2_new(-1,0),errno);
    printf("call dup2_new of %s file,new file description(10) is %d\n",argv[1],dup2_new(fd,10));
}
