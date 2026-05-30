#define _POSIX_C_SOURCE 200809L
#include "group.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Group *group_create(const char *name, const char *mc_ip, int mc_port) {
    Group *g = malloc(sizeof(Group));
    if (!g) return NULL;
    strncpy(g->name,         name,  MAX_GROUP_NAME_LEN - 1);
    g->name[MAX_GROUP_NAME_LEN - 1] = '\0';
    strncpy(g->multicast_ip, mc_ip, 15);
    g->multicast_ip[15]  = '\0';
    g->multicast_port    = mc_port;
    g->members           = list_create();
    g->member_count      = 0;
    return g;
}

void group_destroy(Group *g) {
    if (!g) return;
    list_destroy(g->members, free);
    free(g);
}

int group_add_member(Group *g, const char *username) {
    char *uname;
    if (!g || group_has_member(g, username)) return -1;
    uname = strdup(username);
    if (list_push_back(g->members, uname) != 0) { free(uname); return -1; }
    g->member_count++;
    return 0;
}

static int _cmp_str(void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}

int group_remove_member(Group *g, const char *username) {
    ListNode *node;
    if (!g) return -1;
    node = list_find(g->members, (void *)username, _cmp_str);
    if (!node) return -1;
    list_remove(g->members, (void *)username, _cmp_str);
    g->member_count--;
    return 0;
}

int group_has_member(Group *g, const char *username) {
    if (!g) return 0;
    return list_find(g->members, (void *)username, _cmp_str) != NULL;
}

int group_member_count(Group *g) {
    return g ? g->member_count : 0;
}