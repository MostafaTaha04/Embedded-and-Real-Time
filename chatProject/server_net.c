#define _POSIX_C_SOURCE 200809L
#include "server_net.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

ServerNet *server_net_create(int port) {
    int              i;
    int              opt = 1;
    struct sockaddr_in addr;
    ServerNet *sn = calloc(1, sizeof(ServerNet));
    if (!sn) return NULL;
    for (i = 0; i < MAX_CLIENTS; i++) sn->client_fds[i] = -1;

    sn->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sn->server_fd < 0) { perror("socket"); free(sn); return NULL; }

    setsockopt(sn->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(port);

    if (bind(sn->server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind"); close(sn->server_fd); free(sn); return NULL;
    }
    if (listen(sn->server_fd, 10) < 0) {
        perror("listen"); close(sn->server_fd); free(sn); return NULL;
    }
    printf("[ServerNet] Listening on port %d\n", port);
    return sn;
}

void server_net_destroy(ServerNet *sn) {
    int i;
    if (!sn) return;
    for (i = 0; i < MAX_CLIENTS; i++)
        if (sn->client_fds[i] != -1) close(sn->client_fds[i]);
    close(sn->server_fd);
    free(sn);
}

int server_net_accept(ServerNet *sn) {
    int                i;
    int                fd;
    struct sockaddr_in addr;
    socklen_t          len = sizeof(addr);
    fd = accept(sn->server_fd, (struct sockaddr *)&addr, &len);
    if (fd < 0) { perror("accept"); return -1; }
    for (i = 0; i < MAX_CLIENTS; i++) {
        if (sn->client_fds[i] == -1) {
            sn->client_fds[i] = fd;
            sn->client_count++;
            printf("[ServerNet] New client fd=%d from %s\n",
                   fd, inet_ntoa(addr.sin_addr));
            return fd;
        }
    }
    fprintf(stderr, "[ServerNet] Too many clients\n");
    close(fd);
    return -1;
}

int server_net_remove_client(ServerNet *sn, int fd) {
    int i;
    for (i = 0; i < MAX_CLIENTS; i++) {
        if (sn->client_fds[i] == fd) {
            close(fd);
            sn->client_fds[i] = -1;
            sn->client_count--;
            return 0;
        }
    }
    return -1;
}

int server_net_recv(int fd, ClientRequest *req) {
    int n = recv(fd, req, sizeof(ClientRequest), MSG_WAITALL);
    if (n <= 0) return -1;
    return 0;
}

int server_net_send(int fd, ServerResponse *res) {
    int n = send(fd, res, sizeof(ServerResponse), 0);
    return (n == (int)sizeof(ServerResponse)) ? 0 : -1;
}

int server_net_build_fdset(ServerNet *sn, fd_set *set) {
    int i;
    int max_fd;
    FD_ZERO(set);
    FD_SET(sn->server_fd, set);
    max_fd = sn->server_fd;
    for (i = 0; i < MAX_CLIENTS; i++) {
        if (sn->client_fds[i] != -1) {
            FD_SET(sn->client_fds[i], set);
            if (sn->client_fds[i] > max_fd) max_fd = sn->client_fds[i];
        }
    }
    return max_fd;
}