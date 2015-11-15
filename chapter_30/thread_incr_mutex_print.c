#include <pthread.h>
#include "tlpi_hdr.h"

struct st_thread{
    int loops;
    char *thName;
};

static int glob = 0;
static pthread_mutex_t mtx;

static void * threadFunc(void *arg)   /* Loop 'arg' times incrementing 'glob' */
{
    struct st_thread *st_th = ((struct st_thread *)arg);
    int loops = st_th->loops;
    int loc,j,s;

    for (j = 0; j < loops; j++)
    {
        s = pthread_mutex_lock(&mtx);
        if (s != 0)
        {
            errExitEN(s,"pthread_mutex_lock");
        }

        printf("%s before operation glob = %d ",st_th->thName,glob);
        loc = glob;
        loc++;
        glob = loc;
        printf(", after operation glob = %d\n",glob);
        
        s = pthread_mutex_unlock(&mtx);
        if (s != 0)
        {
            errExitEN(s,"pthread_mutex_lock");
        }
    }

    return NULL;
}

int main(int argc,char *argv[])
{
    pthread_t t1,t2;
    struct st_thread st_th1,st_th2;
    int loops,s;

    loops = (argc > 1) ? getInt(argv[1],GN_GT_0,"num-loops") : 10000000;

    st_th1.loops = loops;
    st_th2.loops = loops;
    st_th1.thName = "Thread 1";
    st_th2.thName = "Thread 2";

    s = pthread_mutex_init(&mtx,NULL);
    if (s != 0)
    {
        errExitEN(s,"pthread_mutex_init");
    }
    
    s = pthread_create(&t1,NULL,threadFunc,&st_th1);
    if (s != 0)
    {
        errExitEN(s,"pthread_create");
    }

    s = pthread_create(&t2,NULL,threadFunc,&st_th2);
    if (s != 0)
    {
        errExitEN(s,"pthread_create");
    }

    s = pthread_join(t1,NULL);
    if (s != 0)
    {
        errExitEN(s,"pthread_join");
    }

    s = pthread_join(t2,NULL);
    if (s !=  0)
    {
        errExitEN(s,"pthread_join");
    }

    s = pthread_mutex_destroy(&mtx);
    if (s != 0)
    {
        errExitEN(s,"pthread_mutex_destroy");
    }
    
    printf("glob = %d\n",glob);
    exit(EXIT_SUCCESS);
}