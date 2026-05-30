/* client_mng.h */
#ifndef CLIENT_MNG_H
#define CLIENT_MNG_H

#include "client_net.h"
#include "client_groups_mng.h"

typedef struct {
    ClientNet       *net;
    ClientGroupsMng *groups;
    char             username[MAX_USERNAME_LEN];
    char             server_ip[16];
    int              logged_in;
} ClientMng;

ClientMng *client_mng_create(const char *server_ip);
void       client_mng_destroy(ClientMng *cm);
int        client_mng_register(ClientMng *cm, const char *user, const char *pass);
int        client_mng_login(ClientMng *cm, const char *user, const char *pass);
int        client_mng_logout(ClientMng *cm);
int        client_mng_create_group(ClientMng *cm, const char *gname);
int        client_mng_join_group(ClientMng *cm, const char *gname);
int        client_mng_leave_group(ClientMng *cm, const char *gname);
void       client_mng_exit(ClientMng *cm);
/* last server message (for UI display) */
const char *client_mng_last_msg(ClientMng *cm);

#endif /* CLIENT_MNG_H */