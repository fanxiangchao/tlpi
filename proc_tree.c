/**
 * tlpi Excercise 12-2
 * Show process tree like 'pstree' command
 * init(1)----
 *            |
 *            |
 *            xxxxxx(pid,ppid)
 *            ...
 * author:fanxiangchao
 **/
#define _GNU_SOURCE
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include "mylib.h"
#include "tlpi_hdr.h"

#define FLAGS_LENGTH 80
#define PROC_NAME_LENGTH_MAX 50
#define FORMAT_LENGTH 80
#define BUF_SIZE 200

struct procNode{
    int pos;
    char name[PROC_NAME_LENGTH_MAX];
    pid_t pid;
    pid_t ppid;
    struct procNode *next;
};

typedef struct procNode * procNodePtr;

char flags[FLAGS_LENGTH];
char tail[5] = "----";
void printProcTree(procNodePtr procNodeHead,pid_t parent,int pos)
{
    procNodePtr procChild;
    procNodePtr tmpPtr;
    procNodePtr prePtr;
    char format[FORMAT_LENGTH];
    char procStr[50];
    
    procChild = (struct procNode *) malloc(sizeof(struct procNode));
    if (procChild == NULL)
    {
        return;
    }

    
    procChild->next = NULL;
    prePtr = procNodeHead;
    for (tmpPtr = procNodeHead->next; tmpPtr != NULL;)
    {
        if (tmpPtr->ppid == parent)
        {
            //printf("find\n");
            prePtr->next = tmpPtr->next;
            tmpPtr->next = procChild->next;
            procChild->next = tmpPtr;
            tmpPtr = prePtr->next;
        }
        else
        {
            prePtr = tmpPtr;
            tmpPtr = tmpPtr->next;
        }
    }

    //snprintf(format,FORMAT_LENGTH,"%%%ds",(pos - 1));
    //printf("format:%s\n",format);
    snprintf(format,pos + 1,"%s",flags);
    flags[pos] = '|';

    if (procChild->next != NULL)
    {
        printf("%s",tail);
    }

    printf("\n");
    for (tmpPtr = procChild; tmpPtr->next != NULL;)
    {
        snprintf(procStr,sizeof(procStr),"(%d,%d)",tmpPtr->next->pid,tmpPtr->next->ppid);
        printf("%s\n",flags);
        printf("%s\n",flags);
        //printf(format,"");
        printf("%s",format);
        printf("%s%s",tmpPtr->next->name,procStr);
        //printf("--");
        //printf("(%d,%d)\n",tmpPtr->next->pid,tmpPtr->next->ppid);
        
        if (tmpPtr->next->next == NULL)
        {
            flags[pos] = ' ';
        }
        
        printProcTree(procNodeHead,tmpPtr->next->pid,pos + strlen(tmpPtr->next->name) + strlen(procStr)
            + strlen(tail));

        prePtr = tmpPtr;
        tmpPtr = tmpPtr->next;
        if (prePtr != procChild)
        {
            free(prePtr);
        }
        // procChild->next = procChild->next->next;
        //free(tmpPtr->next);
        // tmpPtr = procChild;
    }

    //printf("%d\n",parent);
    flags[pos] = ' ';
    free(procChild);
}

int main(int argc,char *argv[])
{
    int i;
    DIR *dirp;
    struct dirent *dp;
    procNodePtr procNodeHead;
    procNodePtr node;
    char line[BUF_SIZE];
    char path[BUF_SIZE];
    char name[BUF_SIZE];
    char value[BUF_SIZE];
    int fd;

    procNodeHead = (struct procNode *) malloc(sizeof(struct procNode));
    if (procNodeHead == NULL)
    {
        errExit("malloc");
    }
    procNodeHead->next = NULL;
    
    dirp = opendir("/proc");
    if (dirp == NULL)
    {
        errMsg("opendir failed on '%s'","/proc");
        return;
    }

    for (i = 0; i < FLAGS_LENGTH; i++)
    {
        flags[i] = ' ';
    }

    flags[FLAGS_LENGTH - 1] = '\0';
    
    for (;;)
    {
        errno = 0;
        dp = readdir(dirp);
        if (dp == NULL)
        {
            break;
        }

        if (strcmp(dp->d_name,".") == 0 || strcmp(dp->d_name,"..") == 0
            || strcmp(dp->d_name,"1") == 0)
        {
            continue;
        }

        if (dp->d_type != DT_DIR || !isdigit((unsigned char) dp->d_name[0]))
            continue;
        
        memset(path,BUF_SIZE,0);
        strcpy(path,"/proc/");
        strcat(path,dp->d_name);
        strcat(path,"/status");

        //printf("file path:%s\n",path);
        fd = open(path,O_RDONLY,S_IRUSR | S_IRGRP | S_IROTH);
        if (fd == -1 && ENOENT)
        {
            printf("file %s not exist!!! \n",dp->d_name);
            continue;
        }
        else if (fd == -1)
        {
            continue;
        }

        node = (struct procNode *) malloc(sizeof(struct procNode));
        if (node == NULL)
        {
            errMsg("malloc error!!!");
            continue;
        }
        
        for (;;)
        {
            memset(line,0,BUF_SIZE);
            readLine(line,BUF_SIZE,fd);

            if (strlen(line) == 0)
            {
                break;
            }

            //printf("line:%s\n",line);
            sscanf(line,"%s %s",name,value);

            if (strcmp(name,"Name:") == 0)
            {
                strcpy(node->name,value);
            }

            if (strcmp(name,"Pid:") == 0)
            {
                node->pid = getInt(value,GN_NONNEG,"pid");
            }

            if (strcmp(name,"PPid:") == 0)
            {
                node->ppid = getInt(value,GN_NONNEG,"ppid");
                break;
            }
        }

        node->next = procNodeHead->next;
        procNodeHead->next = node;
        
    }

    printf("init(1)");
    /* sizeof("init(1)") + strlen(tail) */
    printProcTree(procNodeHead,1,11);
    
    if (closedir(dirp) == -1)
    {
        errExit("close dir");
    }
}