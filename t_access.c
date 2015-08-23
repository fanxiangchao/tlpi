/**
 * tlpi Exercise 15-4
 * author:fanxiangchao
 **/
#define _BSD_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tlpi_hdr.h"

int access_new(const char *pathname, int mode)
{
    struct stat sb;
    int rst;
    uid_t uid;
    gid_t gid;

    uid = geteuid();
    gid = getegid();
    
    rst = stat(pathname,&sb);
    
    if (rst == -1 && mode == F_OK)
    {
        return 0;
    }

    if (rst == -1)
    {
        return -1;
    }

    if (uid != sb.st_uid || gid != sb.st_gid)
    {
        return -1;
    }
    
    if (mode & R_OK)
    {
        if (!((sb.st_mode & S_IRUSR) && (sb.st_mode & S_IRGRP)))
        {
            return -1;
        }
    }

    if (mode & W_OK)
    {
        if (!((sb.st_mode & S_IWUSR) && (sb.st_mode & S_IWGRP)))
        {
            return -1;
        }
    }

    if (mode & X_OK)
    {
        if (!((sb.st_mode & S_IXUSR) && (sb.st_mode & S_IXGRP)))
        {
            return -1;
        }
    }

    return 0;
}

int main(int argc,char *argv[])
{

    if (argc < 2 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s filename\n",argv[0]);
    }

    int acc = access_new(argv[1],F_OK);
    printf("%s F_OK %d\n",argv[1],acc);
    acc = access_new(argv[1],R_OK | F_OK);
    printf("%s F_OK|R_OK %d\n",argv[1],acc);
    acc = access_new(argv[1],R_OK | W_OK | F_OK);
    printf("%s F_OK|R_OK|W_OK %d\n",argv[1],acc);
    acc = access_new(argv[1],R_OK | W_OK | X_OK);
    printf("%s R_OK|W_OK|X_OK %d\n",argv[1],acc);
    
}

