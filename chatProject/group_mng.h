/* group_mng.h */
#ifndef GROUP_MNG_H
#define GROUP_MNG_H

#include "group_hash.h"
#include "free_mc_ip_queue.h"

#define GROUP_BASE_PORT 6000

typedef struct {
    GroupHash     *groups;
    FreeMcIpQueue *mc_pool;
    int            next_port;
} GroupMng;

GroupMng *group_mng_create(void);
void      group_mng_destroy(GroupMng *gm);
Group    *group_mng_create_group(GroupMng *gm, const char *name);
int       group_mng_delete_group(GroupMng *gm, const char *name);
Group    *group_mng_get_group(GroupMng *gm, const char *name);
int       group_mng_add_member(GroupMng *gm, const char *gname, const char *uname);
/* returns 1 if group was deleted (count reached 0) */
int       group_mng_remove_member(GroupMng *gm, const char *gname, const char *uname);
int       group_mng_exists(GroupMng *gm, const char *name);
/* remove user from every group they're in */
void      group_mng_remove_user_all(GroupMng *gm, const char *uname);

#endif /* GROUP_MNG_H */