/**
 * tlpi Example 16-1
 * author:fanxiangchao
 **/

#include <sys/xattr.h>
#include "tlpi_hdr.h"

#define XATTR_SIZE 10000

static void usageError(char *progName)
{
    fprintf(stderr,"Usage: %s [-x] file...\n",progName);
    exit(EXIT_FAILURE);
}

int main(int argc,char *argv[])
{
    char name[255];
    char value[100];
    int isRemove;
    ssize_t listLen,valueLen;
    int ns,j,k,opt;
    
    isRemove = 0;
    while((opt = getopt(argc,argv,"u:v:x:")) != -1)
    {
        switch (opt)
        {
            case 'u':
                strncpy(name,optarg,strlen(optarg));
                break;
            case 'v':
                strncpy(value,optarg,strlen(optarg));
                break;
            case 'x':
                isRemove = 1;
                strncpy(name,optarg,strlen(optarg));
                break;
            case '?':
                //usageError(argv[0]);
                break;
        }
    }

    
    
    if (!isRemove)
    {
        setxattr(argv[optind],name,value,sizeof(value),0);
    }
    else
    {
        printf("remove EA name=%s\n",name);
        removexattr(argv[optind],name);
    }
}