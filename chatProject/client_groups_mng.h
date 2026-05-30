/* client_groups_mng.h */
#ifndef CLIENT_GROUPS_MNG_H
#define CLIENT_GROUPS_MNG_H

#include "ds.h"
#include <sys/types.h>

#define MAX_GROUP_NAME_LEN 32

typedef struct {
    char  name[MAX_GROUP_NAME_LEN];
    char  multicast_ip[16];
    int   multicast_port;
    pid_t sender_pid;     /* PID of the multicast sender   subprocess */
    pid_t receiver_pid;   /* PID of the multicast receiver subprocess */
} ClientGroup;

typedef struct {
    HashTable *groups;   /* key = group name, value = ClientGroup* */
} ClientGroupsMng;

ClientGroupsMng *cgm_create(void);
void             cgm_destroy(ClientGroupsMng *cgm);
int              cgm_add(ClientGroupsMng *cgm, const char *name,
                          const char *mc_ip, int mc_port,
                          pid_t sender_pid, pid_t receiver_pid);
ClientGroup     *cgm_get(ClientGroupsMng *cgm, const char *name);
int              cgm_remove(ClientGroupsMng *cgm, const char *name);
int              cgm_exists(ClientGroupsMng *cgm, const char *name);
void             cgm_remove_all(ClientGroupsMng *cgm);

#endif /* CLIENT_GROUPS_MNG_H */