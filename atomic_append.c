/*
 * tlpi excesise 5-3 
 */
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int fd;
    off_t off;
    ssize_t numWrite;
    int i;
    int numBytes;
    mode_t flags;
    Boolean app;
    
    if (argc < 3 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s filename num-bytes [x]\n",argv[0]);
    }

    if (argc == 4 && strcmp(argv[3],"x") == 0)
    {
        flags = O_RDWR | O_CREAT;
        app = FALSE;
    }
    else
    {
        flags = O_RDWR | O_APPEND | O_CREAT;
        app = TRUE;
    }

    numBytes = atoi(argv[2]);
    printf("numBytes = %d\n",numBytes);
    fd = open(argv[1],flags);
    if (fd == -1)
    {
        errExit("open");
    }

    if (app == FALSE)
    {
        off = lseek(fd,0,SEEK_END);
    }

    for (i = 0; i < numBytes; i++)
    {
        numWrite = write(fd,"A",1);
        if (numWrite == -1)
        {
            errExit("write");
        }
    }

    if (close(fd) == -1)
    {
        errExit("close");
    }
    
    exit(EXIT_SUCCESS);
    
}