/**
 * tlpi Exercise 12-3
 * author:fanxiangchao
 **/

#define _GNU_SOURCE
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include "tlpi_hdr.h"
#include "mylib.h"

#define MAX_FILE_PATH 100
#define MAX_LINE_LENGTH 300

int isOpenFile(const char *path,const char *filename)
{
    DIR *dirp;
    struct dirent *dp;
    char tmp[MAX_FILE_PATH];
    ssize_t numBytes;
    char buf[MAX_FILE_PATH];
    
    dirp = opendir(path);
    if (dirp == NULL)
    {
        return 0;
    }
    
    for (;;)
    {
        dp = readdir(dirp);
        if (dp == NULL)
        {
            break;
        }

        if (dp->d_type != DT_LNK || strcmp(dp->d_name,".") == 0
            || strcmp(dp->d_name,"..") == 0)
        {
            continue;
        }

        memset(tmp,MAX_FILE_PATH,0);
        strcpy(tmp,path);
        strcat(tmp,"/");
        strcat(tmp,dp->d_name);
        //printf("%s\n",tmp);
        
        numBytes = readlink(tmp,buf,MAX_FILE_PATH - 1);
        if (numBytes == -1)
        {
            return 0;
        }

        buf[numBytes] = '\0';
        //printf("%s\n",buf);
        if (strcmp(buf,filename) == 0)
        {
            return 1;
        }
        
    }

    if (closedir(dirp) == -1)
    {
        return 0;
    }

    return 0;
}

void getProcName(const char *spid,char *procname)
{
    char path[MAX_FILE_PATH];
    char line[MAX_LINE_LENGTH];
    char name[50];
    char value[MAX_LINE_LENGTH];
    int fd;

    if (spid == NULL || procname == NULL)
    {
        return;
    }

    memset(path,MAX_FILE_PATH,0);
    strcpy(path,"/proc/");
    strcat(path,spid);
    strcat(path,"/status");

    fd = open(path,O_RDONLY);
    if (fd == -1)
    {
        errMsg("open %s\n",path);
        return;
    }

    for (;;)
    {
        line[0] = '\0';
        readLine(line,MAX_LINE_LENGTH,fd);

        if (strlen(line) == 0)
        {
            break;
        }

        memset(value,MAX_LINE_LENGTH,0);
        sscanf(line,"%s %s",name,value);
        if (strcmp(name,"Name:") == 0)
        {
            strcpy(procname,value);
            procname[strlen(value)] = '\0';
            break;
        }
    }
    
    if (close(fd) == -1)
    {
        errMsg("close file %s\n",path);
    }
}

int main(int argc,char *argv[])
{
    char path[MAX_FILE_PATH];
    char procname[100];
    DIR *dirp;
    struct dirent *dp;

    if (argc < 2 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("usage:%s filepath\n",argv[0]);
    }

    /* Open dir */
    dirp = opendir("/proc");
    if (dirp == NULL)
    {
        errExit("open dir");
    }

    printf("                 This proc open file %s\n",argv[1]);
    printf("==================================================================\n");
    printf("%-40s%15s\n","Name","PID");
    printf("==================================================================\n");
    /* transfer dir */
    for (;;)
    {
        memset(path,MAX_FILE_PATH,0);
        errno = 0;
        dp = readdir(dirp);

        if (dp == NULL)
        {
            break;
        }
        
        if (dp->d_type != DT_DIR || strcmp(dp->d_name,".") == 0
            || strcmp(dp->d_name,"..") == 0 || !isdigit((unsigned char)dp->d_name[0]))
        {
            continue;
        }

        strcpy(path,"/proc/");
        strcat(path,dp->d_name);
        strcat(path,"/fd");

        if (isOpenFile(path,argv[1]) == 1)
        {
            getProcName(dp->d_name,procname);
            printf("%-40s%15d\n",procname,getInt(dp->d_name,GN_NONNEG,"pid"));
        }
    }

    if (closedir(dirp) == -1)
    {
        errExit("close dir");
    }
}

