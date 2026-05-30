#define _POSIX_C_SOURCE 200809L
#include "client_net.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

ClientNet *client_net_create(const char *server_ip, int port) {
    struct sockaddr_in addr;
    ClientNet *cn = malloc(sizeof(ClientNet));
    if (!cn) return NULL;

    cn->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (cn->socket_fd < 0) { perror("socket"); free(cn); return NULL; }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(port);
    if (inet_pton(AF_INET, server_ip, &addr.sin_addr) <= 0) {
        fprintf(stderr, "Invalid server IP\n");
        free(cn);
        return NULL;
    }
    if (connect(cn->socket_fd,
                (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");
        free(cn);
        return NULL;
    }
    return cn;
}

void client_net_destroy(ClientNet *cn) {
    if (!cn) return;
    close(cn->socket_fd);
    free(cn);
}

int client_net_send(ClientNet *cn, ClientRequest *req) {
    int n = send(cn->socket_fd, req, sizeof(ClientRequest), 0);
    return (n == (int)sizeof(ClientRequest)) ? 0 : -1;
}

int client_net_recv(ClientNet *cn, ServerResponse *res) {
    int n = recv(cn->socket_fd, res, sizeof(ServerResponse), MSG_WAITALL);
    return (n <= 0) ? -1 : 0;
}