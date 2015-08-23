/**
 * tlpi Exercise 18-4
 * author:fanxiangchao
 **/
#include <dirent.h>
#include <stddef.h>
#include <limits.h>
#include "tlpi_hdr.h"

#define NAME_MAX_LEN PATH_MAX

/**
 * List all files in directory 'dirpath'
 */
static void listFiles(const char *dirpath)
{
    DIR *dirp;
    struct dirent *entryp;
    struct dirent *result;
    size_t len;
    Boolean isCurrent; /* True if 'dirpath' is "." */

    isCurrent = strcmp(dirpath,".") == 0;

    dirp = opendir(dirpath);
    if (dirp == NULL)
    {
        errMsg("opendir failed on '%s'",dirpath);
        return;
    }

    len = offsetof(struct dirent,d_name) + NAME_MAX_LEN + 1;
    entryp = (struct dirent *)malloc(len);
    if (entryp == NULL)
    {
        errExit("malloc");
    }

    result = (struct dirent *)malloc(len);
    if (result == NULL)
    {
        errExit("malloc");
    }
    
    /* For each entry in this directory,print directory + filename */
    for (;;)
    {
        errno = 0;   /* To distinguish error from end-of-directory */
        //dp = readdir(dirp);
        if (readdir_r(dirp,entryp,&result) != 0)
        {
            errExit("readdir_r");
        }
        
        if (result == NULL)
        {
            break;
        }

        if (strcmp(result->d_name,".") == 0 || strcmp(result->d_name,"..") ==0)
        {
            continue;   /* Skip . and .. */
        }

        if (!isCurrent)
        {
            printf("%s/",dirpath);
        }

        printf("%s\n",result->d_name);
    }

    free(entryp);
    free(result);
    
    if (errno != 0)
    {
        errExit("readdir");
    }

    if (closedir(dirp) == -1)
    {
        errMsg("closedir");
    }
}

int main(int argc,char *argv[])
{
    if (argc > 1 && strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s [dir...]\n",argv[0]);
    }

    if (argc == 1)
    {
        listFiles(".");
    }
    else
    {
        for (argv++; *argv; argv++)
        {
            listFiles(*argv);
        }
    }

    exit(EXIT_SUCCESS);
}