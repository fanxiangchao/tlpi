/*
 * tlpi Exercise 7-2
 * Impl malloc memory and free it
 * Not adjust program break when big free block near to program break,
 * maybe do it in future :)
 * author:fanxiangchao
 */

#include "tlpi_hdr.h"
#define MEM_PAGE_SIZE 8192
#define MIN_MALLOC_SIZE 32

typedef struct DoubleLink
{
    size_t size;
    struct DoubleLink *pre;
    struct DoubleLink *next;
}DoubleLink;

struct DoubleLink fh;

DoubleLink *free_head = &fh;

void initFree()
{
    free_head->size = 0;
    free_head->pre = free_head;
    free_head->next = free_head;
}

void insertAsc(DoubleLink *ptr);

void *malloc_new(size_t size)
{
    char *pos;
    char *tmp;
    DoubleLink *link;
    DoubleLink *newLink;
    DoubleLink *pre;
    DoubleLink *next;
    size_t linkSize;
    intptr_t allocSize;
    size_t minMallocSize;
    
    pos = NULL;
    linkSize = sizeof(struct DoubleLink);
    link = free_head->next;

    size = size < MIN_MALLOC_SIZE ? MIN_MALLOC_SIZE : size;
    
    while(link != free_head)
    {
        //printf("free_head->pre:%10p\n",link->pre);
        if (link->size > (size + linkSize))
        {
            //printf("linkSize=%d\n",linkSize);
            tmp = (char *)link;
            pre = link->pre;
            next = link->next;
            newLink = (DoubleLink *)(tmp + size + sizeof(size_t));
            // printf("newLink=%10p\n",newLink);
            newLink->size = (link->size - size - sizeof(size_t));
            newLink->pre = pre;
            newLink->next = next;

            pre->next = newLink;
            // printf("link=%10p\n",link)
            *((size_t *)tmp) = size;
            pos = tmp + sizeof(size_t);
            //printf("pos=%10p\n",pos);
            return pos;
        }
        else
        {
            link = link->next;
        }
    }
    
    tmp = (char *)sbrk(MEM_PAGE_SIZE);
    printf("sbark address: %10p\n",tmp);
    *((size_t *)tmp) = size;
    pos =(tmp + sizeof(size_t));

    /* left memory and insert into free link */
    newLink = (DoubleLink *) (tmp + sizeof(size_t) + size);
    newLink->size = MEM_PAGE_SIZE - size - 2 * sizeof(size_t);
    newLink->pre = NULL;      /* insert at head */
    newLink->next = NULL;

    insertAsc(newLink);
    
    printf("free_head: %10p, %10p, %10p \n",free_head,free_head->pre,free_head->next);
    return pos;
    
}

int getSizeFree()
{
    DoubleLink *ptr;
    int size = 0;
    for (ptr = free_head->next; ptr != free_head; ptr = ptr->next)
    {
        size++;
    }

    return size;
}

char *computDoubleLinkTail(DoubleLink *ptr)
{
    char *p;
    p = (char *)ptr;
    //printf("size:%d\n",sizeof(DoubleLink *));
    return p + sizeof(size_t) + 2 * sizeof(DoubleLink *) + ptr->size;
}

size_t getDoubleLinkLength(DoubleLink *ptr)
{
    return ptr->size + sizeof(size_t) + 2 * sizeof(DoubleLink *);
}

void insertAsc(DoubleLink *ptr)
{
    DoubleLink *link;
    char *ptrEnd;
    char *p;
    
    link = ptr;
    p = (char *)ptr;
    ptrEnd = computDoubleLinkTail(ptr); 

    
    for (link = free_head->next; link != free_head; link = link->next)
    {
        
        p = computDoubleLinkTail(link);
        //printf("***** %10p, %10p, %10p ,%d\n",link,p,ptr,ptr->size);
        /* merge nearly block */
        if (p == (char *)ptr)
        {
            printf("near head %10p\n",link->next);
            link->size += getDoubleLinkLength(ptr);
            ptr = link;
            link->pre->next = link->next;
            link->next->pre = link->pre;
            link = link->pre;
                
            //printf("%10p,%10p\n",ptrEnd,ptr->next);
        }
        else if (ptrEnd == (char *)link)
        {
            printf("near tail\n");
            ptr->size += getDoubleLinkLength(link);
            link->pre->next = link->next;
            link->next->pre = link->pre;
            link = link->pre;
            break;
        }
    }
    
    for (link = free_head->next; link != free_head; link = link->next)
    {
        if (link->size > ptr->size)
        {
            //printf("^^^ %10p,%10p\n",link,ptr);
            break;
        }
    }

    link->pre->next = ptr;
    ptr->pre = link->pre;
    ptr->next = link;
}

void free_new(void *ptr)
{
    char *p;
    DoubleLink *link;
    DoubleLink *pre;

    if (ptr == NULL)
    {
        printf("null do nothing\n");
    }
    
    p = (char *)ptr;
    link = (DoubleLink *) ( p - sizeof(size_t) );
    
    link->size = link->size - 2 * sizeof(DoubleLink *);
    link->pre = NULL;
    link->next = NULL;
    //printf("##### %10p,%d\n",link,link->size);
    insertAsc(link);
}

int main(int argc,char *argv[])
{
    char *ptr[100];
    int numAllocs;
    int blockSize;
    int i;
    
    if (argc < 3 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s numAllocs blockSize\n",argv[0]);
    }

    initFree();
    
    numAllocs = getInt(argv[1],GN_GT_0,"numAllocs");
    blockSize = getInt(argv[2],GN_GT_0,"blockSize");

    numAllocs = numAllocs > 100 ? 100:numAllocs;

    for (i = 0; i < numAllocs; i++)
    {
        ptr[i] = (char *)malloc_new(blockSize);
        printf("ptr[%d]: %10p\n",i,ptr[i]);
        if (ptr[i] == NULL)
        {
            printf("malloc_new error\n");
            errExit("malloc");
        }
    }

    printf("free head: %10p,%d\n",free_head->next,free_head->next->size);
    printf("========== Free Memory ==========\n");
    for (i = 0; i < numAllocs; i++)
    {
        free_new(ptr[i]);
        printf("free size %d\n",getSizeFree());
    }

    printf("********* End **********\n");
    exit(EXIT_SUCCESS);
}