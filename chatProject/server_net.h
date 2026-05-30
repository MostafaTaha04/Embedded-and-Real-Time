/* server_net.h */
#ifndef SERVER_NET_H
#define SERVER_NET_H

#include "protocol.h"
#include <sys/select.h>

#define MAX_CLIENTS 64

typedef struct {
    int server_fd;
    int client_fds[MAX_CLIENTS];
    int client_count;
} ServerNet;

ServerNet *server_net_create(int port);
void       server_net_destroy(ServerNet *sn);
int        server_net_accept(ServerNet *sn);       /* returns new fd or -1 */
int        server_net_remove_client(ServerNet *sn, int fd);
int        server_net_recv(int fd, ClientRequest *req);
int        server_net_send(int fd, ServerResponse *res);
/* fills fd_set; returns max_fd */
int        server_net_build_fdset(ServerNet *sn, fd_set *set);

#endif /* SERVER_NET_H */