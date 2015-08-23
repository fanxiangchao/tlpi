/**
 * tlpi Exercise
 * author:fanxiangchao
 **/

#include <sys/stat.h>
#include <limits.h>
#include "tlpi_hdr.h"

#define BUF_SIZE PATH_MAX

char *t_realpath(const char *pathname,char *resolved_path)
{
    char *rpath;
    struct stat statbuf;
    char buf[BUF_SIZE];
    char r_buf[BUF_SIZE];
    char cwdbuf[BUF_SIZE];
    ssize_t numBytes;
    size_t sz;
    size_t i;
    size_t j;
    size_t k;
    
    if (resolved_path == NULL)
    {
        rpath = (char *)malloc(PATH_MAX * sizeof(char));
        if (rpath == NULL)
        {
            errExit("malloc");
        }
    }
    else
    {
        rpath = resolved_path;
    }

    if (lstat(pathname,&statbuf) == -1)
    {
        printf("cannot get %s stat,maybe file not exist!",pathname);
        errExit("lstat");
    }
    
    if (S_ISLNK(statbuf.st_mode))
    {
        numBytes = readlink(pathname,buf,BUF_SIZE - 1);
        if (numBytes == -1)
        {
            printf("cannot read %s path from soft link",pathname);
            errExit("readlink");
        }
    }
    else
    {
        strncpy(buf,pathname,BUF_SIZE);
    }

    getcwd(cwdbuf,BUF_SIZE);
    if (buf[0] != '/')
    {
        strncpy(r_buf,cwdbuf,BUF_SIZE);
        sz = strlen(r_buf);
        r_buf[sz] = '/';
        strncpy(&r_buf[sz + 1],buf,BUF_SIZE);
    }
    else
    {
        strncpy(r_buf,buf,BUF_SIZE);
    }

    sz = strlen(r_buf);
    j = 0;
    for (i = 0; i < sz;)
    {
        if (r_buf[i] != '.')
        {
            rpath[j++] = r_buf[i++];
        }
        else if (r_buf[i + 1] == '.')
        {
            //find '..'
            for (k = j - 1; k >=0; k--)
            {
                if (r_buf[k] == '/')
                {
                    j = k + 1;
                    break;
                }
            }

            i = i + 3;
        }else if (r_buf[i + 1] == '/')
        {
            //find '.'
            i += 2;
        }else
        {
            rpath[j++] = r_buf[i++];
        }
    }

    rpath[j] = '\0';
    return rpath;
}

int main(int argc,char *argv[])
{

    int i;
    char path[BUF_SIZE];
    if (argc < 2 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s pathname1 pathname2 ...\n",argv[0]);
    }

    for (i = 1; i < argc; i++)
    {
        t_realpath(argv[i],path);
        printf("[%s] = %s\n",argv[i],path);
    }

    exit(EXIT_SUCCESS);
}