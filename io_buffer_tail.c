/**
 * tlpi Exercise 13-5
 * author:fanxiangchao
 **/
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define IO_BUF_SIZE 4096

off_t findloc(int fd,char *buf,int bufsize,int lineNum)
{
    off_t off;
    off_t endoff;
    int num;
    ssize_t numRead;
    ssize_t i;
    num = lineNum;
    
    endoff = lseek(fd,0,SEEK_END);
    off = endoff - bufsize;
    off = off > 0 ? off : 0;
    
    while(off >= 0)
    {
        lseek(fd,off,SEEK_SET);
        numRead = read(fd,buf,bufsize);
        i = numRead - 1;
        while(i >= 0 && num > 0)
        {
            if (buf[i] == '\n')
            {
                num--;
            }
            i--;
        }

        if (num != 0 && off > 0)
        {
            off = off - bufsize;
            off = off > 0 ? off : 0;
        }
        else if (num != 0 && off == 0)
        {
            return 0;
        }else
        {
            return off + i + 2;
        }
    }

    return 0;
}

int main(int argc,char *argv[])
{
    int lineNum = 10;
    int opt;
    char *pstr;
    int fd;
    char *buf;
    int idx = 1;
    off_t off;
    ssize_t numRead;
    
    if (argc < 2 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s [-n num] file\n",argv[0]);
    }

    while((opt = getopt(argc,argv,":n:")) != -1)
    {
        switch(opt)
        {
            case 'n': pstr = optarg;lineNum = getInt(pstr,GN_GT_0,"line number");break;
            case ':': usageErr("%s Missing argument %c\n",argv[0],optopt);
            case '?': usageErr("%s Unrecongnized option %c\n",argv[0],optopt);
            default:fatal("Unexpected case in switch()");
        }
    }

    if (optind == argc)
    {
        usageErr("%s Missing file name\n",argv[0]);
    }
    
    buf = (char *)malloc(sizeof(char) * IO_BUF_SIZE);
    if (buf == NULL)
    {
        errExit("malloc");
    }

    fd = open(argv[optind],O_RDONLY);
    if (fd == -1)
    {
        errExit("open");
    }
    
    off = findloc(fd,buf,IO_BUF_SIZE, lineNum);
    lseek(fd,off,SEEK_SET);
    while((numRead = read(fd,buf,IO_BUF_SIZE)) > 0)
    {
        printf("%s",buf);
        buf[numRead] = '\0';
    }

    printf("\n");
    free(buf);
}
 