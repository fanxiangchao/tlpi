/**
 * tlpi Exercise
 * author:fanxiangchao
 **/

#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include "tlpi_hdr.h"
#include "mylib.h"

#define BUF_SIZE 200

/*
 * Return UID corresponding to 'name', or -1 on error
 */
uid_t userIdFromName(const char *name)
{
    struct passwd *pwd;
    uid_t u;
    char *endptr;

    if (name == NULL || *name == '\0')
    {
        return -1;
    }

    /* As a convenience to caller,allow a numeric string */
    u = strtol(name,&endptr,10);
    if (*endptr == '\0')
    {
        return u;
    }

    pwd = getpwnam(name);
    if (pwd == NULL)
    {
        return -1;
    }

    return pwd->pw_uid;
}

/**
 * read line from file
 * Maybe some bugs to be modified
 **/
/*
void readLine(char *buf,size_t size,int fd)
{
    char *pbuf;
    size_t idx = -1;
    size_t rdl = 0;
    off_t offset;
    
    pbuf = (char *)malloc(BUF_SIZE + 1);
   if (pbuf == NULL)
   {
       errExit("malloc");
   }

    pbuf[BUF_SIZE] = '\0';

    rdl = read(fd,pbuf,BUF_SIZE);

    //printf("line-> : %s\n",pbuf);
    while (rdl > 0)
    {
        for (idx = 0; idx < rdl; idx++)
        {
            if (pbuf[idx] == '\n')
            {
                break;
            }
        }

        if (idx == rdl)
        {
            if (size < rdl)
            {
                strncpy(buf,pbuf,size);
                break;
            }
            else
            {
                strncpy(buf,pbuf,rdl);
                rdl = read(fd,pbuf,BUF_SIZE);
            }
        }
        else
        {
            if (size < idx)
            {
                strncpy(buf,pbuf,size);
            }
            else
            {
                strncpy(buf,pbuf,idx);
            }

            offset = lseek(fd,0,SEEK_CUR);
            lseek(fd,1 - (rdl - idx),SEEK_CUR);
            break;
        }
    }

    free(pbuf);
    
}
*/
int main(int argc,char *argv[])
{
    int fd;
    DIR *dirp;
    struct dirent *dp;
    char buf[BUF_SIZE];
    char line[BUF_SIZE];
    char name[BUF_SIZE];
    char value[BUF_SIZE];
    char proc_name[100];
    uid_t upid;
    uid_t uid;
    
    if (argc < 2 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("Usage: %s username\n",argv[0]);
    }

    uid = userIdFromName(argv[1]);
    dirp = opendir("/proc");
    if (dirp == NULL)
    {
        errMsg("opendir failed on '%s'", "/proc");
        return;
    }

    for (;;)
    {
        errno = 0;
        dp = readdir(dirp);
        if (dp == NULL)
        {
            break;
        }

        if (strcmp(dp->d_name,".") == 0 || strcmp(dp->d_name,"..") == 0)
            continue;

        memset(buf,0,BUF_SIZE);
        /* /proc/PID/status file path */
        strcpy(buf,"/proc/");
        strcat(buf,dp->d_name);
        strcat(buf,"/status");

//printf("path: %s\n",buf);
        fd = open(buf,O_RDONLY,S_IRUSR | S_IRGRP | S_IROTH
            | S_IWUSR | S_IWGRP | S_IWOTH);
        if (fd == -1 && errno == ENOENT)
        {
            printf("file %s is not exist!!\n",buf);
            continue;
        }
        else if (fd == -1)
        {
// errExit("open");
            continue;
        }

        //printf("path: %s\n",buf);
        for (;;)
        {
            memset(line,0,BUF_SIZE);
            readLine(line,BUF_SIZE,fd);
            //printf("line: %s \n",line);
            sscanf(line,"%s %s",name,value);
            if (strcmp(name,"Name:") == 0)
            {
                strcpy(proc_name,value);
            }
            else if (strcmp(name,"Uid:") == 0)
            {       
                //printf("%s:%d\n",value,strlen(value));
                upid = getInt(value,GN_NONNEG,"upid");
                if (upid == uid)
                {
                    printf("PID: %s, Name: %s\n",dp->d_name,proc_name);
                    break;
                }
                break;
            }
        }

        if (close(fd) == -1)
        {
            errExit("close file");
        }
    }


    exit(EXIT_SUCCESS);
}