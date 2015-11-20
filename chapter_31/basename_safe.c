#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define MAX_BUF_LEN 256

static __thread char buf[MAX_BUF_LEN];

int isEmpty(const char *str)
{
    int length;
    int i;

    if (str == NULL || (length = strlen(str)) == 0)
    {
        return 1;
    }

    for (i = 0; i < length; i++)
    {
        if (*(str + i) != ' ' &&
            *(str + i) != '\t')
        {
            return 0;
        }
    }

    return 1;
}

char *basename_safe(const char *path)
{
    int length;
    int i;
    int start,end;
    
    if (isEmpty(path))
    {
        buf[0] = '.';
        buf[1] = '\0';
        return buf;
    }

    length = strlen(path);
    end = -1;
    for (i = length - 1; i >= 0; i--)
    {
        if (path[i] != '/')
        {
            end = i;
            break;
        }
    }

    if (end < 0)
    {
        buf[0] = '/';
        buf[1] = '\0';
        return buf;
    }else if (end == 0)
    {
        buf[1] = '\0';
        return buf;
    }

    start = -1;
    for (i = end - 1; i >=0; i--)
    {
        if (path[i] == '/')
        {
            start = i;
            break;
        }
    }

    length = (end - start) >= MAX_BUF_LEN ? MAX_BUF_LEN - 1 : (end - start);
    strncpy(buf,path + start + 1,length);
    buf[length] = '\0';

    return buf;
    
}