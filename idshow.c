/*
 * tlpi Example 9-1
 * author:fanxiangchao
 */

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/fsuid.h>
#include <limits.h>
#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include "tlpi_hdr.h"


#define SG_SIZE (NGROUPS_MAX + 1)
/*
 * Return name corresponding to 'uid',or NULL on error
 */
char *userNameFromId(uid_t uid)
{
    struct passwd *pwd;
    pwd = getpwuid(uid);
    return (pwd == NULL) ? NULL : pwd->pw_name;
}

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

/*
 * Return name corresponding to 'gid', or NULL on error
 */
char *groupNameFromId(gid_t gid)
{
    struct group *grp;
    grp = getgrgid(gid);
    return (grp == NULL) ? NULL : grp->gr_name;
}

/*
 * Return GID corresponding to 'name', or -1 on error
 */
gid_t groupIdFromName(const char *name)
{
    struct group *grp;
    gid_t g;
    char *endptr;

    if (name == NULL || *name == '\0')
    {
        return -1;
    }

    g = strtol(name,&endptr,10);
    if (*endptr == '\0')
    {
        return g;
    }

    grp = getgrnam(name);
    if (grp == NULL)
    {
        return -1;
    }

    return grp->gr_gid;
}


int main(int argc,char *argv[])
{
    uid_t ruid,euid,suid,fsuid;
    gid_t rgid,egid,sgid,fsgid;
    gid_t suppGroups[SG_SIZE];
    int numGroups,j;
    char *p;

    if (getresuid(&ruid,&euid,&suid) == -1)
    {
        errExit("getresuid");
    }

    if (getresgid(&rgid,&egid,&sgid) == -1)
    {
        errExit("getresgid");
    }

    fsuid = setfsuid(0);
    fsgid = setfsgid(0);

    printf("UID: ");
    p = userNameFromId(ruid);
    printf("real=%s (%ld);", (p == NULL) ? "???" : p,(long)ruid);
    p = userNameFromId(euid);
    printf("eff=%s (%ld);", (p == NULL) ? "???" : p,(long)euid);
    p = userNameFromId(suid);
    printf("saved=%s (%ld);", (p == NULL) ? "???" : p,(long)suid);
    p = userNameFromId(fsuid);
    printf("fs=%s (%ld);", (p == NULL) ? "???" : p,(long)fsuid);
    printf("\n");

    printf("GID: ");
    p = groupNameFromId(rgid);
    printf("real=%s (%ld);", (p == NULL) ? "???" : p,(long)rgid);
    p = groupNameFromId(egid);
    printf("eff=%s (%ld);", (p == NULL) ? "???" : p,(long)egid);
    p = groupNameFromId(sgid);
    printf("saved=%s (%ld);",(p == NULL) ? "???" : p,(long)sgid);
    p = groupNameFromId(fsgid);
    printf("fs=%s (%ld);",(p == NULL) ? "???" : p,(long)fsgid);
    printf("\n");

    numGroups = getgroups(SG_SIZE,suppGroups);
    if (numGroups == -1)
    {
        errExit("getgroups");
    }

    printf("Supplementary groups (%d):",numGroups);
    for (j = 0; j < numGroups; j++)
    {
        p = groupNameFromId(suppGroups[j]);
        printf("%s (%ld) ",(p == NULL) ? "???" : p,(long)suppGroups[j]);
    }
    printf("\n");

    exit(EXIT_SUCCESS);
    
}