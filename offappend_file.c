#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int fd;
    off_t off;
    ssize_t numWrite;
    
    if (argc != 3 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s file string\n",argv[0]);
    }

    fd = open(argv[1],O_RDWR | O_APPEND,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (fd == -1)
    {
        errExit("open");
    }

    off = lseek(fd,0,SEEK_SET);
    printf("write %s into file %s,with length %d\n",argv[2],argv[1],strlen(argv[2]));
    numWrite = write(fd,argv[2],strlen(argv[2]));
    if (numWrite == -1)
    {
        errExit("write");
    }

    exit(EXIT_SUCCESS);
}