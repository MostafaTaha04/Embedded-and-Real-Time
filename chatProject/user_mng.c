#define _POSIX_C_SOURCE 200809L
#include "user_mng.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

UserMng *user_mng_create(void) {
    UserMng *um = malloc(sizeof(UserMng));
    if (!um) return NULL;
    um->users = user_hash_create();
    return um;
}

void user_mng_destroy(UserMng *um) {
    if (!um) return;
    user_hash_destroy(um->users);
    free(um);
}

int user_mng_register(UserMng *um, const char *username,
                       const char *password, int socket_fd) {
    User *u;
    if (user_hash_exists(um->users, username)) {
        fprintf(stderr, "[UserMng] Username '%s' already exists\n", username);
        return -1;
    }
    u = user_create(username, password, socket_fd);
    if (!u) return -1;
    return user_hash_add(um->users, u);
}

int user_mng_login(UserMng *um, const char *username,
                    const char *password, int socket_fd) {
    User *u = user_hash_get(um->users, username);
    if (!u) {
        fprintf(stderr, "[UserMng] User '%s' not found\n", username);
        return -1;
    }
    if (strcmp(u->password, password) != 0) {
        fprintf(stderr, "[UserMng] Wrong password for '%s'\n", username);
        return -1;
    }
    u->is_active = 1;
    u->socket_fd = socket_fd;
    return 0;
}

int user_mng_logout(UserMng *um, const char *username) {
    User *u = user_hash_get(um->users, username);
    if (!u) return -1;
    u->is_active = 0;
    u->socket_fd = -1;
    return 0;
}

User *user_mng_get(UserMng *um, const char *username) {
    return user_hash_get(um->users, username);
}