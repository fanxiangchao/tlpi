/**
 * mylib.c
 * author:fanxiangchao
 **/

#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include "tlpi_hdr.h"

#define BUF_SIZE 200

/**
 * read line from file
 * Maybe some bugs to be modified
 **/
void readLine(char *buf,size_t size,int fd)
{
    char *pbuf;
    size_t idx = -1;
    size_t rdl = 0;
    off_t offset;
    
    pbuf = (char *)malloc(BUF_SIZE + 1);
   if (pbuf == NULL)
   {
       errExit("malloc");
   }

    pbuf[BUF_SIZE] = '\0';

    rdl = read(fd,pbuf,BUF_SIZE);

    //printf("line-> : %s\n",pbuf);
    while (rdl > 0)
    {
        for (idx = 0; idx < rdl; idx++)
        {
            if (pbuf[idx] == '\n')
            {
                break;
            }
        }

        if (idx == rdl)
        {
            if (size < rdl)
            {
                strncpy(buf,pbuf,size);
		buf[size] = '\0';
                break;
            }
            else
            {
                strncpy(buf,pbuf,rdl);
		buf[rdl] = '\0';
                rdl = read(fd,pbuf,BUF_SIZE);
            }
        }
        else
        {
            if (size < idx)
            {
                strncpy(buf,pbuf,size);
		buf[size] = '\0';
            }
            else
            {
                strncpy(buf,pbuf,idx);
		buf[idx] = '\0';
            }

            offset = lseek(fd,0,SEEK_CUR);
            lseek(fd,1 - (rdl - idx),SEEK_CUR);
            break;
        }
    }

    free(pbuf);
    
}