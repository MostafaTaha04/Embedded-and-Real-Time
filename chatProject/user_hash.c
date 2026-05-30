#define _POSIX_C_SOURCE 200809L
#include "user_hash.h"
#include <stdlib.h>

UserHash *user_hash_create(void) {
    UserHash *uh = malloc(sizeof(UserHash));
    if (!uh) return NULL;
    uh->table = hash_create();
    return uh;
}

void user_hash_destroy(UserHash *uh) {
    if (!uh) return;
    hash_destroy(uh->table, (void(*)(void *))user_destroy);
    free(uh);
}

int user_hash_add(UserHash *uh, User *u) {
    return hash_insert(uh->table, u->username, u);
}

User *user_hash_get(UserHash *uh, const char *username) {
    return (User *)hash_lookup(uh->table, username);
}

int user_hash_remove(UserHash *uh, const char *username) {
    return hash_remove(uh->table, username, NULL);
}

int user_hash_exists(UserHash *uh, const char *username) {
    return hash_lookup(uh->table, username) != NULL;
}