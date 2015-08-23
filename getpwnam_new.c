/*
 * tlpi Exercise 8-2
 * implement function of getpwnam() use setpwent() getpwent() endpwent()
 * author:fanxiangchao
 */

#include <pwd.h>
#include <ctype.h>
#include "tlpi_hdr.h"

struct passwd *getpwnam_new(const char *name)
{
    struct passwd *pwd;
    setpwent();

    while((pwd = getpwent()) != NULL)
    {
        if (strcmp(pwd->pw_name,name) == 0)
        {
            endpwent();
            return pwd;
        }
    }

    endpwent();

    return NULL;
}

int main(int argc,char *argv[])
{
    struct passwd *pwd;

    pwd = getpwnam_new("root");
    if (pwd == NULL)
    {
        errExit("could't get pwssword of user \n'","root");
    }

    printf("username: %s\n",pwd->pw_name);
    printf("password: %s\n",pwd->pw_passwd);
    printf("userID: %ld\n",(long)pwd->pw_uid);
    printf("groupID: %ld\n",(long)pwd->pw_gid);
    printf("comment: %s\n",pwd->pw_gecos);
    printf("Initial working(home) directory: %s\n",pwd->pw_dir);
    printf("Login shell: %s\n",pwd->pw_shell);

    exit(EXIT_SUCCESS);
}