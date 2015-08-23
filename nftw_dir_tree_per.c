/**
 * tlpi Exercise 18-7
 * author:fanxiangchao
 **/
#define _XOPEN_SOURCE 600
#include <ftw.h>
#include "tlpi_hdr.h"

int perArr[5];
int total = 0;

static int dirTree(const char *pathname,const struct stat *sbuf,
    int type,struct FTW *ftwb)
{

    if (type == FTW_NS)
    {
        perArr[8] = perArr[8] + 1;
        total++;
        return 0;
    }

    switch(sbuf->st_mode & S_IFMT)
    {
        case S_IFREG: perArr[0] = perArr[0] + 1; break;
        case S_IFDIR: perArr[1] = perArr[1] + 1; break;
        case S_IFCHR: perArr[2] = perArr[2] + 1; break;
        case S_IFBLK: perArr[3] = perArr[3] + 1; break;
        case S_IFLNK: perArr[4] = perArr[4] + 1; break;
        case S_IFIFO: perArr[5] = perArr[5] + 1; break;
        case S_IFSOCK:perArr[6] = perArr[6] + 1; break;
        default:
            perArr[7] = perArr[7] + 1; break;
    }
    
    total++;

    return 0;
}

int main(int argc,char *argv[])
{
    int flags;

    if (argc < 2 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("usage:%s directory\n",argv[0]);
    }

    flags = FTW_PHYS | FTW_MOUNT;
    if (nftw(argv[1],dirTree,10,flags) == -1)
    {
        exit(EXIT_FAILURE);
    }

    printf("================================================================\n");
    printf("Reg file: %d, %.2f%%\n",perArr[0],(float)perArr[0] * 100 / total);
    printf("Dir file: %d, %2.f%%\n",perArr[1],(float)perArr[1] * 100 / total);
    printf("Chr file: %d, %2.f%%\n",perArr[2],(float)perArr[2] * 100 / total);
    printf("blk file: %d, %2.f%%\n",perArr[3],(float)perArr[3] * 100 / total);
    printf("Lnk file: %d, %2.f%%\n",perArr[4],(float)perArr[4] * 100 / total);
    printf("IFO file: %d, %2.f%%\n",perArr[5],(float)perArr[5] * 100 / total);
    printf("SOCK file: %d, %2.f%%\n",perArr[6],(float)perArr[6] * 100 / total);
    printf("Oth file: %d, %2.f%%\n",perArr[7],(float)perArr[7] * 100 / total);
    printf("err file:%d, %2.f%%\n",perArr[8],(float)perArr[8] * 100 / total);
    printf("Total: %d\n",total);
    
    exit(EXIT_SUCCESS);
}