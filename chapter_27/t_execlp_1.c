#include "tlpi_hdr.h"

extern int t_execlp_impl(const char *filename,const char *arg,...);

int main(int argc,char *argv[])
{
    if (argc != 2 || strcmp(argv[1],"--help") == 0)
    {
        usageErr("%s pathname\n",argv[0]);
    }

    t_execlp_impl(argv[1],argv[1],"hello world",(char *)NULL);
    errExit("execlp");   /* If we get here, something went wrong */
}