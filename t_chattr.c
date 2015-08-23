/**
 * tlpi Exercise 15-5
 * author:fanxiangchao
 **/

#include <sys/types.h>
#include <sys/stat.h>
#include <linux/fs.h>
#include "tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int attr;
    int attrOld;
    char optrate;
    int i;
    int fd;
    
    if (argc < 3 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s +-=[acdeijstuACDST] file \n",argv[0]);
    }

    optrate = argv[1][0];
    for (i = 1; i < strlen(argv[1]); i++)
    {
        switch(argv[1][i])
        {
            case 'a':
                attr |= FS_APPEND_FL;
                break;
            case 'c':
                attr |= FS_COMPR_FL;
                break;
            case 'd':
                attr |= FS_NODUMP_FL;
                break;
            case 'i':
                attr |= FS_IMMUTABLE_FL;
                break;
            case 'j':
                attr |= FS_JOURNAL_DATA_FL;
                break;
            case 's':
                attr |= FS_SECRM_FL;
                break;
            case 't':
                attr |= FS_NOTAIL_FL;
                break;
            case 'u':
                attr |= FS_UNRM_FL;
                break;
            case 'A':
                attr |= FS_NOATIME_FL;
                break;
            case 'C':
                break;
            case 'D':
                attr |= FS_DIRSYNC_FL;
                break;
            case 'S':
                attr |= FS_SYNC_FL;
                break;
            case 'T':
                attr |= FS_TOPDIR_FL;
                break;
            default:
                printf("invalid attr %c \n",argv[1][i]);
                break;
        }
    }

    if (attr == 0)
    {
        usageErr("%s +-=[acdeijstuACDST] file \n",argv[0]);
    }

    fd = open(argv[2],S_IRUSR);
    if (fd == -1)
    {
        errExit("open");
    }

    if (ioctl(fd,FS_IOC_GETFLAGS,&attrOld) == -1)
    {
        errExit("ioctl get");
    }

    if (optrate == '+')
    {
        attrOld |= attr;
    }
    else if (optrate == '-')
    {
        attrOld &= (~attr);
    }
    else if (optrate == '=')
    {
        attrOld = attr;
    }
    else
    {
        if (close(fd) == -1)
        {
            printf("close file %s error\n",argv[2]);
        }
        printf("invalid operate character %c  \n",optrate);
        usageErr("%s +-=[acdeijstuACDST] file \n",argv[0]);
    }
    
    if (ioctl(fd,FS_IOC_SETFLAGS,&attrOld) == -1)
    {
        close(fd);
        errExit("ioctl set");
    }

    return EXIT_SUCCESS;
}