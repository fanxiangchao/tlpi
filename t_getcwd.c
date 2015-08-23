/**
 * tlpi Exercise 18-5
 * Get current directory
 * author:fanxiangchao
 **/

#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define BUF_SIZE PATH_MAX

char *t_getcwd(char *cwdbuf,size_t size)
{
    char *buf;
    char name[BUF_SIZE];
    char parentName[BUF_SIZE];
    char tmp[BUF_SIZE];
    size_t bufSize;
    struct stat parentStat;
    struct stat cwdStat;
    struct stat fileStat;
    DIR *dirp;
    struct dirent *dp;
    size_t pos;
    size_t left;
    size_t len_name;
    int fd;
    ino_t pt;
    ino_t ct;
    int i;
    int j;
    
    fd = open(".",O_RDONLY);
    
    dirp = opendir("..");
    if (dirp == NULL)
    {
        errMsg("opendir failed on '..'");
        return NULL;
    }

    if (stat(".",&cwdStat) == -1)
    {
        errMsg("cannot get stat of current");
        return NULL;
    }

    if (stat("..",&parentStat) == -1)
    {
        errMsg("cannot get stat of current parent");
        return NULL;
    }
    
    if (cwdbuf == NULL)
    {
        bufSize = (size == 0 ? BUF_SIZE : size);
        buf = (char *)malloc(bufSize);
    }else
    {
        buf = cwdbuf;
        bufSize = size;
    }

    parentName[0] = '.';
    parentName[1] = '.';
    parentName[2] = '/';
    pos = 0;
    //printf("parent.st_ino=%d,cwdStat.st_ino=%d\n",parentStat.st_ino,cwdStat.st_ino);
    while(pos < BUF_SIZE && (parentStat.st_ino != cwdStat.st_ino || parentStat.st_dev != cwdStat.st_dev))
    {

        errno = 0;
        for (;;)
        {
            dp = readdir(dirp);
            if (dp == NULL)
            {
                if (errno != 0)
                {
                    printf("error when readdir\n");
                }
                else
                {
                    printf("end...\n");
                }
                break;
            }

            if (strcmp(dp->d_name,".") == 0 || strcmp(dp->d_name,"..") == 0)
            {
                //printf(".. or .\n");
                // printf("%s = %d %d\n",dp->d_name,dp->d_ino,dp->d_type == DT_LNK);
                continue;
            }

            //printf("%s   %d\n",dp->d_name,dp->d_ino);
            strncpy(&parentName[3],dp->d_name,BUF_SIZE - 2);
            if (stat(parentName,&fileStat) == -1)
            {
                errMsg("cannot get stat of %s",parentName);
                break;
            }
            if (fileStat.st_ino == cwdStat.st_ino)
            {
                left = BUF_SIZE - pos;
                //len_name = strlen(dp->d_name);
                strncpy(name,dp->d_name,BUF_SIZE);
                basename(name);
                len_name = strlen(name);
                strncpy(&tmp[pos],name,left);
                //printf("name=%s\n",name);
                if (len_name < left)
                {
                    pos = pos + len_name;
                    tmp[pos] = '/';
                    pos = pos + 1;
                }else
                {
                    pos = pos + left;
                }

                //strncpy(&parentName[2],dp->d_name,BUF_SIZE);
                //strncpy(&parentName[strlen(dp->d_name) + 2],"/../",BUF_SIZE - strlen(dp->d_name));
                break;
            }
        }

        chdir("..");

        if (lstat(".",&cwdStat) == -1)
        {
            errMsg("cannot get stat of '.'");
        }
        
        if (stat("..",&parentStat) == -1)
        {
            errMsg("cannot get stat of '..'");
        }

        //realpath("..",parentName);
        //printf("..=%s\n",parentName);
        //realpath(".",parentName);
        //printf(".=%s\n",parentName);
        
        if (closedir(dirp) == -1)
        {
            errMsg("closedir");
        }
        
        dirp = opendir("..");
        if (dirp == NULL)
        {
            errMsg("opendir failed on '..'");
        }
        //printf("parent.st_ino=%d,cwdStat.st_ino=%d,parent.st_dev=%d,cwdStat.st_dev=%d\n",
        //           parentStat.st_ino,cwdStat.st_ino,parentStat.st_dev,cwdStat.st_dev);
    }

    tmp[pos] = '\0';
    fchdir(fd);
    close(fd);

    //printf("%s,leng=%d\n",tmp,pos);
    i = j = pos - 1;
    pos = 0;
    //buf[pos++] = '/';
    while(i >= 0 && pos < size)
    {
        if (tmp[i] == '/')
        {
            left = bufSize - pos;
            strncpy(&buf[pos],&tmp[i + 1],left > j - i ? j -i : left);
            pos += j - i;
            buf[pos++] =  '/';
            i --;
            j = i;
        }else if (i == 0)
        {
            left = bufSize - pos;
            strncpy(&buf[pos],&tmp[i], left > j - i + 1 ? j - i + 1 : left);
            pos += j- i + 1;
            break;
        }
        else 
        {
            i--;
        }
    }

    buf[pos] = '\0';
    buf[bufSize - 1] = '\0';
    return buf;
    
}

int main(int argc,char *argv[])
{
    char buf[BUF_SIZE];
    char buf1[5];
    t_getcwd(buf,BUF_SIZE);
    printf("current directory: %s %d\n",buf,strlen(buf));
    t_getcwd(buf1,5);
    printf("current directory(buf small):%s %d\n",buf1,strlen(buf1));
}