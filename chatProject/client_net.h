/* client_net.h */
#ifndef CLIENT_NET_H
#define CLIENT_NET_H

#include "protocol.h"

typedef struct {
    int socket_fd;
} ClientNet;

ClientNet *client_net_create(const char *server_ip, int port);
void       client_net_destroy(ClientNet *cn);
int        client_net_send(ClientNet *cn, ClientRequest *req);
int        client_net_recv(ClientNet *cn, ServerResponse *res);

#endif /* CLIENT_NET_H */