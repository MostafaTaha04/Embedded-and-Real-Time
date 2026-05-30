/* server_mng.h */
#ifndef SERVER_MNG_H
#define SERVER_MNG_H

#include "user_mng.h"
#include "group_mng.h"
#include "server_net.h"
#include "protocol.h"

typedef struct {
    UserMng   *user_mng;
    GroupMng  *group_mng;
    ServerNet *net;
} ServerMng;

ServerMng *server_mng_create(int port);
void       server_mng_destroy(ServerMng *sm);
void       server_mng_run(ServerMng *sm);   /* main event loop */
void       server_mng_handle_client(ServerMng *sm, int fd);

#endif /* SERVER_MNG_H */