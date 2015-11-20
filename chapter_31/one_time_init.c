#include <pthread.h>
#include <stdio.h>
#include "once_time_init.h"
#include "tlpi_hdr.h"

int one_time_init(one_time_str *once,void (*func)())
{
    int s;

    s = pthread_mutex_lock(&once->mtx);
    if (s != 0)
    {
        errExitEN(s,"pthread_mutex_lock");
    }

    if (!once->called)
    {
        func();
        once->called = 1;
    }
    
    s = pthread_mutex_unlock(&once->mtx);
    if (s != 0)
    {
        errExitEN(s,"pthread_mutex_unlock");
    }

    return s;
}