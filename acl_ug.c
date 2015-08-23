/**
 * tlpi Exercise 17-1
 * author:fanxiangchao
 **/
#include <acl/libacl.h>
#include <sys/acl.h>
#include "ugid_functions_tlpi.h"
#include "tlpi_hdr.h"

static void usageError(char *progName)
{
    fprintf(stderr,"Usage: %s -u userName or userId | -g groupName or groupId filename\n",progName);
    exit(EXIT_FAILURE);
}

int main(int argc,char *argv[])
{
    acl_t acl;
    acl_type_t type;
    acl_entry_t entry;
    acl_tag_t tag;
    uid_t uid;
    gid_t gid;
    uid_t *uidp;
    gid_t *gidp;
    acl_permset_t permset;
    acl_permset_t maskpermset;
    Boolean isMask;
    char *name;
    int entryId,permVal,opt;

    uid = -1;
    gid = -1;
    type = ACL_TYPE_ACCESS;
    while((opt = getopt(argc,argv,"u:g:")) != -1)
    {
        switch(opt)
        {
            case 'u':
                uid = userIdFromName(optarg);
                break;
            case 'g':
                gid = groupIdFromName(optarg);
                break;
            case '?':
                usageError(argv[0]);
        }
    }

    if (optind + 1 != argc)
    {
        usageError(argv[0]);
    }

    acl = acl_get_file(argv[optind],type);
    if (acl == NULL)
    {
        errExit("acl_get_file");
    }

    //printf("%d,%d, %s\n",uid,gid,argv[optind]);
    for (entryId = ACL_FIRST_ENTRY; ; entryId = ACL_NEXT_ENTRY)
    {
        if (acl_get_entry(acl,entryId,&entry) != 1)
        {
            break;
        }

        if (acl_get_tag_type(entry,&tag) == -1)
        {
            errExit("acl_get_tag_type");
        }

        if (tag == ACL_USER)
        {
            //printf("user\n");
            uidp = acl_get_qualifier(entry);
            if (uidp == NULL)
            {
                errExit("acl_get_qualifier");
            }

            if (uid == *uidp)
            {
                name = userNameFromId(uid);
                if (name == NULL)
                {
                    printf("%-20d",uid);
                }else
                {
                    printf("%-20s",name);
                }

                if (acl_free(uidp) == -1)
                {
                    errExit("acl_free");
                }
            }else
            {
                continue;
            }
        }
        else if (tag == ACL_GROUP)
        {
            gidp = acl_get_qualifier(entry);
            if (gidp == NULL)
            {
                errExit("acl_get_qualifier");
            }

            if (gid == *gidp)
            {
                name = groupNameFromId(gid);
                //printf("name=%s\n",name);
                if (name == NULL)
                {
                    printf("%-20d",gid);
                }
                else
                {
                    printf("%-20s",name);
                }

                if (acl_free(gidp) == -1)
                {
                    errExit("acl_free");
                }
            }
            else
            {
                continue;
            }
        }else if (tag == ACL_MASK)
        {
            isMask = TRUE;
            if (acl_get_permset(entry,&maskpermset) == -1)
            {
                errExit("acl_get_permset");
            }
            continue;
        }else
        {
            continue;
        }

        if (acl_get_permset(entry,&permset) == -1)
        {
            errExit("acl_get_permset");
        }

        permVal = acl_get_perm(permset,ACL_READ);
        if (permVal == -1)
        {
            errExit("acl_get_perm - ACL_READ");
        }

        printf("%c",(permVal == 1) ? 'r':'-');
        permVal = acl_get_perm(permset,ACL_WRITE);
        if (permVal == -1)
        {
            errExit("acl_get_perm - ACL_WRITE");
        }
        printf("%c",(permVal == 1) ? 'w':'-');
        permVal = acl_get_perm(permset,ACL_EXECUTE);
        if (permVal == -1)
        {
            errExit("acl_get_perm - ACL_EXECUTE");
        }
        printf("%c",(permVal == 1) ? 'x':'-');
        
    }

    if (isMask && (uid != -1 || gid != -1))
    {
        printf("         ");
        printf("%c",(acl_get_perm(permset,ACL_READ) & acl_get_perm(maskpermset,ACL_READ)) == 1 ? 'r' : '-');
        printf("%c",(acl_get_perm(permset,ACL_WRITE) & acl_get_perm(maskpermset,ACL_WRITE)) == 1 ? 'w' : '-');
        printf("%c",(acl_get_perm(permset,ACL_EXECUTE) & acl_get_perm(maskpermset,ACL_EXECUTE)) == 1 ? 'x' : '-');
    }

    printf("\n");
    if (acl_free(acl) == -1)
    {
        errExit("acl_free");
    }

    exit(EXIT_SUCCESS);
    
}