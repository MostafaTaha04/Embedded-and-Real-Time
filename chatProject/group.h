/* group.h */
#ifndef GROUP_H
#define GROUP_H

#include "ds.h"
#include <stdint.h>

#define MAX_GROUP_NAME_LEN 32

typedef struct {
    char         name[MAX_GROUP_NAME_LEN];
    char         multicast_ip[16];   /* "239.x.x.x" */
    int          multicast_port;
    LinkedList  *members;            /* list of (char*) usernames */
    int          member_count;
} Group;

Group *group_create(const char *name, const char *mc_ip, int mc_port);
void   group_destroy(Group *g);
int    group_add_member(Group *g, const char *username);
int    group_remove_member(Group *g, const char *username);
int    group_has_member(Group *g, const char *username);
int    group_member_count(Group *g);

#endif /* GROUP_H */