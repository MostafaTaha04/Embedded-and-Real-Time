#define _POSIX_C_SOURCE 200809L
#include "group_mng.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    GroupMng   *gm;
    const char *uname;
} _RemoveCtx;

static void _remove_cb(const char *key, void *val, void *arg) {
    _RemoveCtx *ctx = (_RemoveCtx *)arg;
    Group      *g   = (Group *)val;
    if (group_has_member(g, ctx->uname))
        group_mng_remove_member(ctx->gm, key, ctx->uname);
}

GroupMng *group_mng_create(void) {
    GroupMng *gm = malloc(sizeof(GroupMng));
    if (!gm) return NULL;
    gm->groups    = group_hash_create();
    gm->mc_pool   = mc_queue_create();
    gm->next_port = GROUP_BASE_PORT;
    return gm;
}

void group_mng_destroy(GroupMng *gm) {
    if (!gm) return;
    group_hash_destroy(gm->groups);
    mc_queue_destroy(gm->mc_pool);
    free(gm);
}

Group *group_mng_create_group(GroupMng *gm, const char *name) {
    Group *g;
    int    port;
    char  *mc_ip;
    if (group_hash_exists(gm->groups, name)) return NULL;
    mc_ip = mc_queue_allocate(gm->mc_pool);
    if (!mc_ip) {
        fprintf(stderr, "[GroupMng] No free MC IPs\n");
        return NULL;
    }
    port = gm->next_port++;
    g    = group_create(name, mc_ip, port);
    free(mc_ip);
    if (!g) return NULL;
    group_hash_add(gm->groups, g);
    printf("[GroupMng] Created group '%s' -> %s:%d\n",
           name, g->multicast_ip, port);
    return g;
}

int group_mng_delete_group(GroupMng *gm, const char *name) {
    Group *g = group_hash_get(gm->groups, name);
    if (!g) return -1;
    
    /* FIX: Allocate a fresh copy of the IP to put back into the queue */
    mc_queue_release(gm->mc_pool, strdup(g->multicast_ip));
    
    return group_hash_remove(gm->groups, name);
}

Group *group_mng_get_group(GroupMng *gm, const char *name) {
    return group_hash_get(gm->groups, name);
}

int group_mng_add_member(GroupMng *gm, const char *gname, const char *uname) {
    Group *g = group_hash_get(gm->groups, gname);
    if (!g) return -1;
    return group_add_member(g, uname);
}

int group_mng_remove_member(GroupMng *gm, const char *gname, const char *uname) {
    Group *g = group_hash_get(gm->groups, gname);
    if (!g) return -1;
    group_remove_member(g, uname);
    if (group_member_count(g) == 0) {
        printf("[GroupMng] Group '%s' is empty, deleting\n", gname);
        group_mng_delete_group(gm, gname);
        return 1;
    }
    return 0;
}

int group_mng_exists(GroupMng *gm, const char *name) {
    return group_hash_exists(gm->groups, name);
}

void group_mng_remove_user_all(GroupMng *gm, const char *uname) {
    _RemoveCtx ctx;
    ctx.gm    = gm;
    ctx.uname = uname;
    group_hash_foreach(gm->groups, _remove_cb, &ctx);
}