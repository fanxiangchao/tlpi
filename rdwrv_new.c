/*
 * tlpi excesise 5-7
 * author:fanxiangchao
 */
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include "tlpi_hdr.h"

ssize_t readv_new(int fd,const struct iovec *iov,int iovcnt)
{
    ssize_t numRead,tmp;
    int i;

    numRead = 0;
    for (i = 0; i < iovcnt; i++)
    {
        tmp = read(fd,iov[i].iov_base,iov[i].iov_len);
        if (tmp == -1)
        {
            printf("file eof\n");
            break;
        }

        numRead += tmp;
    }

    return numRead;
}

ssize_t writev_new(int fd,const struct iovec *iov,int iovcnt)
{
    ssize_t numWrite,tmp;
    int i;
    
    numWrite = 0;
    for (i = 0; i < iovcnt; i++)
    {
        tmp = write(fd,iov[i].iov_base,iov[i].iov_len);
        if (tmp == -1)
        {
            printf("write error\n");
            break;
        }

        numWrite += tmp;
    }

    return numWrite;
}

int main(int argc,char *argv[])
{
    int fd_w,fd_r;
    struct iovec w_iovc[2];
    struct iovec r_iovc[2];
    int x = 100;
    ssize_t numWrite = 0;
    ssize_t numRead = 0;
    ssize_t tmp;
    char *buf;
    int y;
    
    if (argc != 3 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s filename string\n",argv[0]);
    }

    fd_w = open(argv[1],O_RDWR | O_CREAT | O_APPEND);
    if (fd_w == -1)
    {
        errExit("open");
    }

    fd_r = open(argv[1],O_RDONLY);
    if (fd_r == -1)
    {
        errExit("open");
    }
    
    w_iovc[0].iov_base = &x;
    w_iovc[0].iov_len = sizeof(x);

    numWrite += w_iovc[0].iov_len;
    
    w_iovc[1].iov_base = argv[2];
    w_iovc[1].iov_len = strlen(argv[2]);

    numWrite += w_iovc[1].iov_len;

    tmp = writev_new(fd_w,w_iovc,2);
    if (tmp < numWrite)
    {
        printf("Write few bytes \n");
    }

    r_iovc[0].iov_base = &y;
    r_iovc[0].iov_len = sizeof(y);

    buf = malloc(w_iovc[1].iov_len);
    if (buf == NULL)
    {
        errExit("malloc");
    }
    
    r_iovc[1].iov_base = buf;
    r_iovc[1].iov_len = w_iovc[1].iov_len;

    numRead = numWrite;
    tmp = readv_new(fd_r,r_iovc,2);
    if (tmp == -1)
    {
        errExit("readv_new");
    }

    if (tmp < numRead)
    {
        printf("Read fewer bytes than requested\n");
    }
    
    printf("read value,%d,%s\n",y,buf);
    free(buf);
    
    if (close(fd_w) == -1)
    {
        errExit("close");
    }

    if (close(fd_r) == -1)
    {
        errExit("close");
    }

    exit(EXIT_SUCCESS);
}