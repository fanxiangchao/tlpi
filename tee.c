#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include "tlpi_hdr.h"

#define printable(ch) (isprint((unsigned char)ch) ? ch : '#')
#define BUF_SIZE 1024

int main(int argc,char *argv[])
{
    size_t len;
    int fd;
    ssize_t numRead,numWritten;
    int opt;
    char *pstr;
    int flags;
    char *buf;
    
    pstr = NULL;
    flags = O_RDWR | O_CREAT | O_TRUNC;

    if (argc < 2 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s [-a] filename\n",argv[0]);
    }
    
    while ((opt = getopt(argc,argv,":a:")) != -1 )
    {
        if (opt == '?' || opt == ':')
        {
            printf("optopt = %3d (%c)\n",optopt,printable(optopt));
        }

        switch(opt)
        {
            case 'a': pstr = optarg; flags = O_RDWR | O_CREAT | O_APPEND; break;
            case ':': usageErr(argv[0],"Missing argument",optopt);
            case '?': usageErr(argv[0],"unreconginzed option",optopt);
            default: fatal("Unexcepted case in switch()");
        }
        
    }

    if (optind < argc)
    {
        pstr = argv[optind];
    }

    fd = open(pstr,flags,S_IRUSR | S_IWUSR | S_IRGRP
        | S_IWGRP | S_IROTH | S_IWOTH);   /* rw-rw-rw */
    if (fd == -1)
    {
        errExit("open");
    }

    buf = malloc(BUF_SIZE);
    while ((numRead = read(STDIN_FILENO,buf,BUF_SIZE)) != -1)
    {
        
        numWritten =  write(STDOUT_FILENO,buf,numRead);
       if (numWritten == -1)
       {
           errExit("write");
       }
       numWritten =  write(fd,buf,numRead);
       if (numWritten == -1)
       {
           errExit("write");
       }
    }

    free(buf);
    if (close(fd) == -1)
    {
        errExit("close");
    }

    exit(EXIT_SUCCESS);
}