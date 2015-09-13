#define _POSIX_C_SOURCE 199309
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include "tlpi_hdr.h"

static void sigintHandler(int sig)
{
    return; /* Just interrupt nanosleep */
}

int main(int argc,char *argv[])
{
    struct timespec start,finish;
    struct timespec request,remain;
    struct sigaction sa;
    int s;

    if (argc != 3 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s secs nanosecs\n",argv[0]);
    }

    /* Allow SIGINT handler to interrupt nanosleep */
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sigintHandler;
    if (sigaction(SIGINT,&sa,NULL) == -1)
    {
        errExit("sigaction");
    }

    if (clock_gettime(CLOCK_REALTIME,&request) == -1)
    {
        errExit("clock_gettime");
    }

    start = request;
    request.tv_sec += getLong(argv[1],0,"secs");
    request.tv_nsec += getLong(argv[2],0,"nsecs");

    if (request.tv_nsec >= 1000000000)
    {
        request.tv_sec += request.tv_nsec / 1000000000;
        request.tv_nsec %= 100000000;
    }
    
    for (;;)
    {
        s = clock_nanosleep(CLOCK_REALTIME,TIMER_ABSTIME,&request,&remain);
        if (s != 0 && s != EINTR)
        {
            errExit("clock_nanosleep");
        }

        if (clock_gettime(CLOCK_REALTIME,&finish) == -1)
        {
            errExit("gettimeofday");
        }

        printf("Slept for: %9.6f secs\n",finish.tv_sec - start.tv_sec +
               (finish.tv_nsec - start.tv_nsec) / 1000000000.0);

        if (s == 0)
        {
            break;     /* clock_nanosleep() completed */
        }

        remain.tv_sec = request.tv_sec - finish.tv_sec;
        remain.tv_nsec = request.tv_nsec - finish.tv_nsec;
        if (remain.tv_nsec < 0)
        {
            remain.tv_nsec += 1000000000;
            remain.tv_sec -= 1;
        }
        
        printf("Remaining: %2ld.%09ld\n",(long)remain.tv_sec,remain.tv_nsec);

    }

    printf("Sleep complete\n");
    exit(EXIT_SUCCESS);
}
