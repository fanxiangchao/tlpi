#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "tlpi_hdr.h"

#define MAX_ARG 100

extern char **environ;

int t_execlp_impl(const char *filename,const char *arg,...)
{
    int i;
    va_list ap;
    char *str;
    char **argVec;
    char *argTmp;
    char *path;
    char filepath[200];
    char *defaultPath = ".:/usr/bin:/bin";
    char *pstr;
    int length;
    int plen;
    int rtVal = -1;
    int morePrefix = 0;
    
    if (filename == NULL)
    {
        return -1;
    }

    argVec = malloc(sizeof(char *) * MAX_ARG);
    if (argVec == NULL)
    {
        errExit("malloc");
    }
    
    va_start(ap,arg);

    i = 0;
    length = strlen(arg);
    argTmp = (char *)malloc(sizeof(char) * (length + 1));
    if (argTmp == NULL)
    {
        errExit("malloc");
    }
    
    strncpy(argTmp,arg,length);
    argTmp[length] = '\0';
    argVec[i++] = argTmp;
    
    while ((str = va_arg(ap,char *)) != NULL && i < MAX_ARG)
    {
        length = strlen(str);
        argTmp = (char *)malloc(sizeof(char) * (length + 1));
        if (argTmp == NULL)
        {
            errExit("malloc");
        }
        strncpy(argTmp,str,length);
        argTmp[length] = '\0';
        argVec[i++] = argTmp;
    }

    va_end(ap);
    
    argVec[i] = (char *)NULL;

    if (strrchr(filename,'/') == (char *)NULL)
    {
        path = getenv("PATH");
        if (path == NULL)
        {
            path = defaultPath;
        }

        length = strlen(filename);
        morePrefix = 1;
        while (morePrefix)
        {
            pstr = strchr(path,':');
            if (pstr == NULL)
            {
                pstr = path + strlen(path);
                morePrefix = 0;
            }
            
            plen = pstr - path;
            strncpy(filepath,path,plen);
            strncpy(filepath + plen,"/",1);
            strncpy(filepath + plen + 1,filename,length);
            filepath[plen + 1 + length] = '\0';

            printf("path : %s\n",filepath);
            rtVal = execve(filepath,argVec,environ);
            path = pstr + 1;

        }
    }else
    {
        return execve(filename,argVec,environ);
    }

    for (i = 0; argVec[i] != NULL;i++)
    {
        free(argVec[i]);
    }
    
    free(argVec);
    
    return rtVal;
}