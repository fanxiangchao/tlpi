/**
 * tlpi Exercise 15-6
 * author:fanxiangchao
 **/

#include <sys/stat.h>
#include <sys/types.h>
#include "tlpi_hdr.h"

int main(int argc,char *argv[])
{
    struct stat sb;
    int i;
    mode_t st_mode;
    
    if (argc < 2 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s file or dir \n",argv[0]);
    }

    for (i = 1; i < argc; i++)
    {
        if (stat(argv[i],&sb) == -1)
        {
            printf("error when get %s stat\n",argv[i]);
        }

        st_mode = sb.st_mode;
        st_mode = st_mode | S_IRUSR | S_IRGRP | S_IROTH
            | S_IXUSR | S_IXGRP | S_IXOTH;

        if (chmod(argv[i],st_mode) == -1)
        {
            printf("error when chmod %s \n",argv[i]);
        }
    }
    
}