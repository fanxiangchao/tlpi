#ifndef _ONCE_TIME_INIT_H
#define _ONCE_TIME_INIT_H
#include <pthread.h>

struct one_time_str
{
    int called;
    pthread_mutex_t mtx;
};

typedef struct one_time_str one_time_str;

#define INIT_ONE_TIME {.called=0,.mtx=PTHREAD_MUTEX_INITIALIZER};

int one_time_init(one_time_str *once,void (*func)());

#endif