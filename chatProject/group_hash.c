#define _POSIX_C_SOURCE 200809L
#include "group_hash.h"
#include <stdlib.h>

GroupHash *group_hash_create(void) {
    GroupHash *gh = malloc(sizeof(GroupHash));
    if (!gh) return NULL;
    gh->table = hash_create();
    return gh;
}

void group_hash_destroy(GroupHash *gh) {
    if (!gh) return;
    hash_destroy(gh->table, (void(*)(void *))group_destroy);
    free(gh);
}

int group_hash_add(GroupHash *gh, Group *g) {
    return hash_insert(gh->table, g->name, g);
}

Group *group_hash_get(GroupHash *gh, const char *name) {
    return (Group *)hash_lookup(gh->table, name);
}

int group_hash_remove(GroupHash *gh, const char *name) {
    return hash_remove(gh->table, name, (void(*)(void *))group_destroy);
}

int group_hash_exists(GroupHash *gh, const char *name) {
    return hash_lookup(gh->table, name) != NULL;
}

void group_hash_foreach(GroupHash *gh,
                        void (*cb)(const char *, void *, void *),
                        void *arg) {
    hash_foreach(gh->table, cb, arg);
}