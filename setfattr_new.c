/**
 * tlpi Exercise 16-1
 * author:fanxiangchao
 **/

#include <sys/xattr.h>
#include "tlpi_hdr.h"


#define NAME_MAX_LENGTH 255
#define VALUE_MAX_LENGTH 10000

static void usageError(char *progName)
{
    fprintf(stderr,"add or modify:\n%s -u name [-v value]"
        "\nremove:\n%s -x name\n",progName,progName);
    exit(EXIT_FAILURE);
}

int main(int argc,char *argv[])
{

    char name[NAME_MAX_LENGTH];
    char value[VALUE_MAX_LENGTH];
    Boolean isRemove = 0;
    int opt;
    
    while((opt = getopt(argc,argv,"n:v:x:")) != -1)
    {
        switch(opt)
        {
            case 'n':
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
                usageError(argv[0]);
                break;
        }
    }
    
    if (!isRemove)
    {
        printf("%s %s %s \n",argv[optind],name,value);
        if (setxattr(argv[optind],name,value,strlen(value),0) == -1)
        {
            errExit("setxattr");
        }
    }
    else
    {
        printf("remove EA name=%s\n",name);
        if(removexattr(argv[optind],name) == -1)
        {
            errExit("removeaxttr");
        }
    }

    exit(EXIT_SUCCESS);
}