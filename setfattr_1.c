/**
 * tlpi Exercise 16-1
 * author:fanxiangchao
 **/

#include <sys/xattr.h>
#include "tlpi_hdr.h"



int main(int argc,char *argv[])
{
    char name[255];
    char value[100];
    int isRemove = 0;
    
    while((opt = getopt(argc,argv,"u:v:x:")) != -1)
    {
        switch(opt)
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

    exit(EXIT_SUCCESS);
}