#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

#define BUF_SIZE 100

ssize_t checkHole(char *buf,ssize_t start,ssize_t length)
{
    ssize_t i;
    for (i = start; i < length; i++)
    {
        if (buf[i] == '\0')
        {
            return i;
        }
    }

    return i;
}

ssize_t findFirstNoEmpty(char *buf,ssize_t start,ssize_t end)
{
    ssize_t i;
    for (i = start; i < end; i++)
    {
        if (buf[i] != '\0')
        {
            return i;
        }
    }

    return i;
}

int main(int argc,char *argv[])
{

    int src_fd,dst_fd;
    char *buf;
    ssize_t numRead,numWritten;
    off_t offset;
    ssize_t fstpos,strpos;
    
    if (argc < 3 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s src_file dst_file\n",argv[0]);
    }

    buf = NULL;
    buf = malloc(BUF_SIZE + 1);
    if (buf == NULL)
    {
        errExit("malloc");
    }

    src_fd = open(argv[1],O_RDONLY,S_IRGRP | S_IRUSR | S_IROTH);
    if (src_fd == -1)
    {
        errExit("open");
    }

    dst_fd = open(argv[2],O_RDWR | O_CREAT,S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
    if (dst_fd == -1)
    {
        errExit("open");
    }

    while((numRead = read(src_fd,buf,BUF_SIZE)) > 0)
    {
        fstpos = checkHole(buf,0,numRead);
        if (fstpos == numRead)
        {
            printf("%ld bytes bufs no hole\n",numRead);
            numWritten = write(dst_fd,buf,numRead);
            if (numWritten == -1)
            {
                error("write");
            }
        }
        else
        {
            printf("find pos at %ld\n",fstpos);
            numWritten = 0;
            while(numWritten < numRead)
            {
                numWritten += write(dst_fd,buf + numWritten,fstpos - numWritten);
                strpos = findFirstNoEmpty(buf,fstpos,numRead);
                numWritten += (strpos - fstpos);
                offset = lseek(dst_fd,strpos - fstpos,SEEK_CUR);
                fstpos = checkHole(buf,numWritten,numRead);
            }
        }
    }

    free(buf);

    if (close(src_fd) == -1)
    {
        errExit("close src file");
    }

    if (close(dst_fd) == -1)
    {
        errExit("close dst file");
    }
    
    exit(EXIT_SUCCESS);
}