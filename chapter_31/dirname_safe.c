#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "tlpi_hdr.h"

static pthread_once_t once = PTHREAD_ONCE_INIT;
static pthread_key_t dirnameKey;

#define MAX_BUF_LEN 256  /* Maximum length of dirname path */
static void destructor(void *buf)
{
    free(buf);
}

static void createKey(void)
{
    int s;
    s = pthread_key_create(&dirnameKey,destructor);
    if (s != 0)
    {
        errExitEN(s,"pthread_key_create");
    }
}

char *dirname_safe(const char *dirname)
{
    int s;
    char *buf;
    int length;
    int idx;
    
    s = pthread_once(&once,createKey);
    if (s != 0)
    {
        errExitEN(s,"pthread_once");
    }

    buf = pthread_getspecific(dirnameKey);
    if (buf == NULL)
    {
        buf = malloc(MAX_BUF_LEN);
        if (buf == NULL)
        {
            errExit("malloc");
        }

        s = pthread_setspecific(dirnameKey,buf);
        if (s != 0)
        {
            errExitEN(s,"pthread_setspecific");
        }
    }
    
    if (dirname == NULL || (length = strlen(dirname)) == 0
        || strchr(dirname,'/') == NULL)
    {
        buf[0] = '.';
        buf[1] = '\0';
        return buf;
    }

    strncpy(buf,dirname,MAX_BUF_LEN - 1);
    buf[MAX_BUF_LEN - 1] = '\0';
    length = strlen(buf);

    idx = length - 1;
    while (idx > 0 && buf[idx] == '/')
    {
        buf[idx] = '\0';
        idx --;
    }

    if (idx == 0 && buf[idx] == '/')
    {
        buf[0] = '/';
        buf[1] = '\0';
        return buf;
    }

    if (idx == 0 && buf[idx] != 0)
    {
        buf[0] = '.';
        buf[1] = '\0';
        return buf;
    }

    while (idx > -1 && buf[idx] != '/')
    {
        buf[idx] = '\0';
        idx --;
    }

    if (idx > 0)
    {
        buf[idx] = '\0';
        return buf;
    }else if (idx == 0)
    {
        return buf;
    }

    buf[0] = '.';
    buf[1] = '\0';
    return buf;
}

