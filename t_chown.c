/**
 * tlpi Example 15-2
 * author:fanxiangchao
 **/

#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>
#include "tlpi_hdr.h"

/*
 * Return UID corresponding to 'name', or -1 on error
 */
uid_t userIdFromName(const char *name)
{
    struct passwd *pwd;
    uid_t u;
    char *endptr;

    if (name == NULL || *name == '\0')
    {
        return -1;
    }

    /* As a convenience to caller,allow a numeric string */
    u = strtol(name,&endptr,10);
    if (*endptr == '\0')
    {
        return u;
    }

    pwd = getpwnam(name);
    if (pwd == NULL)
    {
        return -1;
    }

    return pwd->pw_uid;
}


int main(int argc,char *argv[])
{

}