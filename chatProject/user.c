#define _POSIX_C_SOURCE 200809L
#include "user.h"
#include <stdlib.h>
#include <string.h>

User *user_create(const char *username, const char *password, int socket_fd) {
    User *u = malloc(sizeof(User));
    if (!u) return NULL;
    strncpy(u->username, username, MAX_USERNAME_LEN - 1);
    u->username[MAX_USERNAME_LEN - 1] = '\0';
    strncpy(u->password, password, MAX_PASSWORD_LEN - 1);
    u->password[MAX_PASSWORD_LEN - 1] = '\0';
    u->is_active = 0;
    u->socket_fd = socket_fd;
    return u;
}

void user_destroy(User *u) {
    free(u);
}