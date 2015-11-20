#include <stdio.h>
#include <string.h>       /* Get decalration of strerror() */
#include <pthread.h>
#include "tlpi_hdr.h"

#define MAX_BUF_SIZE 256

extern char *dirname_safe(const char *dirname);

static void *threadFunc(void *arg)
{
    char *str;
    printf("%s --->",(char *)arg);
    str = dirname_safe((char*)arg);
    printf(" %s (address = %p)\n",str,str);
    return NULL;
}

int main(int argc,char *argv[])
{
    pthread_t t;
    int s;
    char *buf[] = {"/home/test/1",
                   "/",
                   "/home/../test/./",
                   "home",
                   "",
                   "/home/test/tlpi///////"};
    int i;
    
    for (i = 0; i < 6; i++)
    {
        s = pthread_create(&t,NULL,threadFunc,buf[i]);
        if (s != 0)
        {
            errExitEN(s,"pthread_create");
        }

        s = pthread_join(t,NULL);
        if (s != 0)
        {
            errExitEN(s,"pthread_join");
        }

    }

    exit(EXIT_SUCCESS);
}