/*
 * tlpi Exercise 6-3
 * author:fanxiangchao
 */

#define _GNU_SOURCE /* To get various declearations from <stdlib.h> */
#include <stdlib.h>
#include "tlpi_hdr.h"

extern char **environ;

int setenv_new(const char *name,const char *value,int overwrite)
{
    char *buf;
    int nameLth,valueLth;
    int total;
    char *tmp;
    
    if (name == NULL || value == NULL)
    {
        printf("name or value cannot be empty\n");
        return -1;
    }

    tmp = getenv(name);
    if (tmp != NULL && overwrite ==0)
    {
        return 0;
    }
    
    nameLth = strlen(name);
    valueLth = strlen(value);
    total = nameLth + valueLth + 2;
    buf = malloc(total);

    if (buf == NULL)
    {
        printf("malloc error\n");
        return -1;
    }
    
    strcpy(buf,name);
    strcpy(buf + nameLth,"=");
    strcpy(buf + nameLth + 1,value);
    buf[total - 1] = '\0';

    printf("put env:%s\n",buf);
    return putenv(buf);
}

int unsetenv_new(const char *name)
{
    char *value;
    char *tmp;

    tmp = malloc(strlen(name) + 1);
    if (tmp == NULL)
    {
        printf("malloc space error\n");
        return -1;
    }
    
    strcpy(tmp,name);
    tmp[strlen(name)] = '\0';
    value = getenv(name);
    while(value != NULL)
    {
        printf("unset env: %s=%s\n",name,value);
        putenv(tmp);
        value = getenv(name);
    }

    free(tmp);
    return 0;
}

void printfEnv()
{
    char **ep;
    printf("-------------- Environment ---------------\n");
    for (ep = environ; *ep != NULL; ep++)
    {
        puts(*ep);
    }
    printf("-------------- Environment End ---------------\n");
}

int main(int argc,char *argv[])
{

    char **ep;

    clearenv();
    printf("--- Set Environment ---\n");
    printf("GREET=Hello World\n"
           "SHELL=/bin/bash\n"
           "LIB=/usr/lib\n"
        "BYE=Linux\n");
    
    setenv_new("GREET","Hello World",1);
    setenv_new("SHELL","/bin/bash",1);
    setenv_new("LIB","/usr/lib",1);
    setenv_new("BYE","Linux",1);

    printfEnv();
    
    setenv_new("GREET","Welcome",0);
    printfEnv();

    unsetenv_new("BYE");
    printfEnv();

    exit(EXIT_SUCCESS);
}