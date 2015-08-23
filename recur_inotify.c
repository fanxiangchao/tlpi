/**
 * tlpi Exercise
 * author:fanxiangchao
 **/
#define _XOPEN_SOURCE 600
#include <sys/inotify.h>
#include <limits.h>
#include <ftw.h>
#include "tlpi_hdr.h"

/*
typedef struct inotify_recur_info * inotify_recur_info_ptr;

typedef struct inotify_recur_info
{
    int wd;
    char *pathname;
    inotify_recur_info_ptr pre;
    inotify_recur_info_ptr next;
}inotify_recur_info;
*/

struct inotify_recur_info
{
    int wd;
    char *pathname;
    struct inotify_recur_info *pre;
    struct inotify_recur_info *next;
};

typedef struct inotify_recur_info *inotify_recur_info_ptr;

typedef struct inotify_recur_info inotify_recur_info;

int inotifyFd;
inotify_recur_info_ptr head;

static int addInotify(const char *pathname)
{
    int wd;
    printf("start to add inotify: %s\n",pathname);
     wd = inotify_add_watch(inotifyFd,pathname,IN_ALL_EVENTS);
     if (wd == -1)
     {
         errExit("inotify_add_watch");
     }
     printf("add watching %d\n",wd);
     return wd;   
}

static void insertInotifyInfoTail(inotify_recur_info *head,inotify_recur_info *info)
{
    if (head == NULL)
    {
        printf("head is null\n");
        return;
    }
    
    if (info == NULL)
    {
        printf("cannot insert null inotify info\n");
        return;
    }

    info->next = head;
    info->pre = head->pre;
    head->pre->next = info;
    head->pre = info;
}

static void addWatchInotify(inotify_recur_info *head, int wd,const char *name)
{
    inotify_recur_info_ptr infoPtr;
    inotify_recur_info_ptr newInfo;
    int nwd;
    char *nameBuf;
    ssize_t len;
    
    if (head == NULL)
    {
        printf("addWatchInotify:head is null\n");
        return;
    }

    infoPtr = head->next;
    for (infoPtr = head->next; infoPtr != head ; infoPtr = infoPtr->next)
    {
        if (infoPtr->wd == wd)
        {
            //find it
            break;
        }
    }

     if (infoPtr != head)
    {
        nameBuf = (char *)malloc(NAME_MAX + 1);
        if (nameBuf == NULL)
        {
            errExit("malloc");
        }

        len = strlen(infoPtr->pathname);
        strncpy(nameBuf,infoPtr->pathname,NAME_MAX);
        nameBuf[len] = '/';
        len = len + 1;
        strncpy(&nameBuf[len],name,NAME_MAX - len);
        len = len + strlen(name);
        nameBuf[len] = '\0';

        nwd = addInotify(nameBuf);
        
        newInfo = (struct inotify_recur_info *)malloc(sizeof(struct inotify_recur_info));
        if (newInfo == NULL)
        {
            free(nameBuf);
            errExit("malloc");
        }
        
        newInfo->wd = nwd;
        newInfo->pathname = nameBuf;
        newInfo->pre = NULL;
        newInfo->next = NULL;

        insertInotifyInfoTail(head,newInfo);

        printf("addwatchInotify parentwd = %d, wd = %d, name = %s, pathname = %s\n",wd,nwd,name,nameBuf);
    }
     else
     {
         nameBuf = (char *)malloc(NAME_MAX + 1);
        if (nameBuf == NULL)
        {
            errExit("malloc");
        }
        len = strlen(name);
        strncpy(nameBuf,name,NAME_MAX);
        nameBuf[len] = '\0';
        newInfo = (struct inotify_recur_info *)malloc(sizeof(struct inotify_recur_info));
        if (newInfo == NULL)
        {
            free(nameBuf);
            errExit("malloc");
        }
        newInfo->wd = wd;
        newInfo->pathname = nameBuf;
        newInfo->pre = NULL;
        newInfo->next = NULL;
        insertInotifyInfoTail(head,newInfo);
        printf("addwatchInotify wd = %d, name = %s, pathname = %s\n",nwd,name,nameBuf);
     }
}

static void displayInotifyEvent(struct inotify_event *i)
{
    printf("    wd=%2d; ",i->wd);
    if (i->cookie > 0)
    {
        printf("cookie = %4d; ", i->cookie);
    }

    printf("mask = ");
    if (i->mask & IN_ACCESS) printf("IN_ACCESS ");
    if (i->mask & IN_ATTRIB) printf("IN_ATTRIB ");
    if (i->mask & IN_CLOSE_NOWRITE) printf("IN_CLOSE_NOWRITE ");
    if (i->mask & IN_CLOSE_WRITE) printf("IN_CLOSE_WRITE ");
    if (i->mask & IN_CREATE) printf("IN_CREATE ");
    if (i->mask & IN_DELETE) printf("IN_DELETE ");
    if (i->mask & IN_DELETE_SELF) printf("IN_DELETE_SELF ");
    if (i->mask & IN_IGNORED) printf("IN_IGNORED ");
    if (i->mask & IN_ISDIR)
    {
        printf("IN_ISDIR ");
    }
    if (i->mask & IN_MODIFY) printf("IN_MODIFY ");
    if (i->mask & IN_MOVE_SELF) printf("IN_MOVE_SELF ");
    if (i->mask & IN_MOVED_FROM) printf("IN_MOVE_FROM ");
    if (i->mask & IN_MOVED_TO) printf("IN_MOVE_TO ");
    if (i->mask & IN_OPEN) printf("IN_OPEN ");
    if (i->mask & IN_Q_OVERFLOW) printf("IN_Q_OVERFLOW ");
    if (i->mask & IN_UNMOUNT) printf("IN_UNMOUNT ");
    printf("\n");

    if (i->len > 0)
    {
        printf("      name = %s\n",i->name);
    }
}

static void removeWatchInotify(inotify_recur_info *head,int wd,char *name)
{
    inotify_recur_info *infoPtr;

    if (head == NULL)
    {
        printf("removeWatchInotify:head is null\n");
        return;
    }

    for (infoPtr = head->next; infoPtr != head; infoPtr = infoPtr->next)
    {
        if (infoPtr->wd == wd)
        {
            break;
        }
    }

    if (infoPtr != head)
    {
        printf("remove watch wd = %d,name = %s,path = %s\n",wd,name,infoPtr->pathname);
        infoPtr->pre->next = infoPtr->next;
        infoPtr->next->pre = infoPtr->pre;
        free(infoPtr);
    }
    else
    {
        printf("not find wd = %d, name = %s\n",wd,name);
    }
}

static int dirTree(const char *pathname,const struct stat *sbuf,int type,
                    struct FTW *ftwb)
{
    int wd;
    if ((sbuf->st_mode & S_IFMT) == S_IFDIR)
    {
        printf("pathname = %s \n",pathname);
        wd = addInotify(pathname);
        addWatchInotify(head,wd,pathname);
    }
    return 0;
}

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int main(int argc,char *argv[])
{
    int wd,j;
    char buf[BUF_LEN];
    ssize_t numRead;
    char *p;
    struct inotify_event *event;
    

    if (argc < 2 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s pathname...\n",argv[0]);
    }

    head = (struct inotify_recur_info *)malloc(sizeof(struct inotify_recur_info));
    if (head == NULL)
    {
        errExit("malloc");
    }
    head->pre = head;
    head->next = head;
    head->wd = -1;
    head->pathname = NULL;
    
    inotifyFd = inotify_init();   /* Create inotify instance */
    if (inotifyFd == -1)
    {
        errExit("inotify_init");
    }

    for (j = 1; j < argc; j++)
    {
        if (nftw(argv[j],dirTree,10,FTW_DEPTH) == -1)
        {
            perror("nftw");
        }
    }

    /* Read events forever */
    for (;;)
    {
        numRead = read(inotifyFd,buf,BUF_LEN);
        if (numRead == 0)
        {
            fatal("read() from inotify fd reaturned 0!");
        }

        if (numRead == -1)
        {
            errExit("read");
        }

        printf("Read %ld bytes from inotify fd\n",(long)numRead);

        /* Process all of the events in buffer returned by read() */
        for (p = buf; p < buf + numRead; )
        {
            event = (struct inotify_event *)p;
            displayInotifyEvent(event);

            /* new dir create */
            if ((event->mask & IN_CREATE) && (event->mask & IN_ISDIR))
            {
                addWatchInotify(head,event->wd,event->name);
            }
            /* dir removed event */
            if (event->mask & (IN_DELETE_SELF))
            {
                printf("remove wd = %d, name = %s\n",event->wd,event->name);
                removeWatchInotify(head,event->wd,event->name);
            }
            p += sizeof(struct inotify_event) + event->len;
        }
    }

    exit(EXIT_SUCCESS);
}