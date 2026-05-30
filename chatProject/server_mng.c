#define _POSIX_C_SOURCE 200809L
#include "server_mng.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

static void _send_ok(int fd, const char *msg) {
    ServerResponse res;
    memset(&res, 0, sizeof(res));
    res.type = RES_OK;
    strncpy(res.message, msg, MAX_MSG_LEN - 1);
    server_net_send(fd, &res);
}

static void _send_err(int fd, const char *msg) {
    ServerResponse res;
    memset(&res, 0, sizeof(res));
    res.type = RES_ERROR;
    strncpy(res.message, msg, MAX_MSG_LEN - 1);
    server_net_send(fd, &res);
}

static void _send_group_info(int fd, Group *g) {
    ServerResponse res;
    memset(&res, 0, sizeof(res));
    res.type           = RES_GROUP_INFO;
    res.multicast_port = g->multicast_port;
    strncpy(res.multicast_ip, g->multicast_ip, 15);
    snprintf(res.message, MAX_MSG_LEN,
             "Joined group '%s' -> %s:%d",
             g->name, g->multicast_ip, g->multicast_port);
    server_net_send(fd, &res);
}

/* FIX: Helper to clean up "Ghost Users" if their terminal abruptly closes */
static void _cleanup_disconnected_client(ServerMng *sm, int fd) {
    int i;
    HashEntry *e;
    if (sm->user_mng && sm->user_mng->users && sm->user_mng->users->table) {
        for (i = 0; i < HASH_TABLE_SIZE; i++) {
            e = sm->user_mng->users->table->buckets[i];
            while (e) {
                User *u = (User *)e->value;
                if (u->is_active && u->socket_fd == fd) {
                    printf("[ServerMng] Cleaning up ghost user '%s'\n", u->username);
                    group_mng_remove_user_all(sm->group_mng, u->username);
                    user_mng_logout(sm->user_mng, u->username);
                    return;
                }
                e = e->next;
            }
        }
    }
}

ServerMng *server_mng_create(int port) {
    ServerMng *sm = malloc(sizeof(ServerMng));
    if (!sm) return NULL;
    sm->user_mng  = user_mng_create();
    sm->group_mng = group_mng_create();
    sm->net       = server_net_create(port);
    if (!sm->user_mng || !sm->group_mng || !sm->net) {
        server_mng_destroy(sm);
        return NULL;
    }
    return sm;
}

void server_mng_destroy(ServerMng *sm) {
    if (!sm) return;
    user_mng_destroy(sm->user_mng);
    group_mng_destroy(sm->group_mng);
    server_net_destroy(sm->net);
    free(sm);
}

void server_mng_handle_client(ServerMng *sm, int fd) {
    ClientRequest req;
    Group        *g;
    memset(&req, 0, sizeof(req));

    if (server_net_recv(fd, &req) != 0) {
        printf("[ServerMng] Client fd=%d disconnected unexpectedly\n", fd);
        _cleanup_disconnected_client(sm, fd); /* Trigger the new cleanup function */
        server_net_remove_client(sm->net, fd);
        return;
    }

    switch (req.type) {
    case MSG_REGISTER:
        if (user_mng_register(sm->user_mng,
                               req.username, req.password, fd) == 0)
            _send_ok(fd, "Registration successful");
        else
            _send_err(fd, "Username already exists");
        break;

    case MSG_LOGIN:
        if (user_mng_login(sm->user_mng,
                            req.username, req.password, fd) == 0)
            _send_ok(fd, "Login successful");
        else
            _send_err(fd, "Invalid username or password");
        break;

    case MSG_LOGOUT:
        group_mng_remove_user_all(sm->group_mng, req.username);
        user_mng_logout(sm->user_mng, req.username);
        _send_ok(fd, "Logout successful");
        break;

    case MSG_CREATE_GROUP:
        g = group_mng_create_group(sm->group_mng, req.group_name);
        if (!g) {
            _send_err(fd, "Group name taken or no resources");
            break;
        }
        group_mng_add_member(sm->group_mng, req.group_name, req.username);
        _send_group_info(fd, g);
        break;

    case MSG_JOIN_GROUP:
        g = group_mng_get_group(sm->group_mng, req.group_name);
        if (!g) {
            _send_err(fd, "Group does not exist");
            break;
        }
        group_mng_add_member(sm->group_mng, req.group_name, req.username);
        _send_group_info(fd, g);
        break;

    case MSG_LEAVE_GROUP:
        if (!group_mng_exists(sm->group_mng, req.group_name)) {
            _send_err(fd, "Group does not exist");
            break;
        }
        group_mng_remove_member(sm->group_mng,
                                 req.group_name, req.username);
        _send_ok(fd, "Left group");
        break;

    case MSG_EXIT:
        group_mng_remove_user_all(sm->group_mng, req.username);
        _send_ok(fd, "Bye");
        server_net_remove_client(sm->net, fd);
        break;

    default:
        _send_err(fd, "Unknown request");
        break;
    }
}

void server_mng_run(ServerMng *sm) {
    int    i;
    int    max_fd;
    int    fd;
    fd_set set;
    printf("[ServerMng] Server running\n");
    while (1) {
        max_fd = server_net_build_fdset(sm->net, &set);
        if (select(max_fd + 1, &set, NULL, NULL, NULL) < 0) {
            perror("select");
            break;
        }
        if (FD_ISSET(sm->net->server_fd, &set))
            server_net_accept(sm->net);

        for (i = 0; i < MAX_CLIENTS; i++) {
            fd = sm->net->client_fds[i];
            if (fd != -1 && FD_ISSET(fd, &set))
                server_mng_handle_client(sm, fd);
        }
    }
}