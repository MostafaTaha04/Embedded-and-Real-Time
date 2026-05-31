#define _POSIX_C_SOURCE 200809L
#include "client_groups_mng.h"
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>

ClientGroupsMng *cgm_create(void) {
    ClientGroupsMng *cgm = malloc(sizeof(ClientGroupsMng));
    if (!cgm) return NULL;
    cgm->groups = hash_create();
    return cgm;
}

static void _free_cg(void *ptr) {
    ClientGroup *cg = (ClientGroup *)ptr;
    if (cg->sender_pid   > 0) kill(cg->sender_pid,   SIGKILL);
    if (cg->receiver_pid > 0) kill(cg->receiver_pid, SIGKILL);
    free(cg);
}

void cgm_destroy(ClientGroupsMng *cgm) {
    if (!cgm) return;
    hash_destroy(cgm->groups, _free_cg);
    free(cgm);
}

int cgm_add(ClientGroupsMng *cgm, const char *name,
             const char *mc_ip, int mc_port,
             pid_t sender_pid, pid_t receiver_pid) {
    ClientGroup *cg = malloc(sizeof(ClientGroup));
    if (!cg) return -1;
    strncpy(cg->name,         name,  MAX_GROUP_NAME_LEN - 1);
    cg->name[MAX_GROUP_NAME_LEN - 1] = '\0';
    strncpy(cg->multicast_ip, mc_ip, 15);
    cg->multicast_ip[15]  = '\0';
    cg->multicast_port    = mc_port;
    cg->sender_pid        = sender_pid;
    cg->receiver_pid      = receiver_pid;
    return hash_insert(cgm->groups, name, cg);
}

ClientGroup *cgm_get(ClientGroupsMng *cgm, const char *name) {
    return (ClientGroup *)hash_lookup(cgm->groups, name);
}

int cgm_remove(ClientGroupsMng *cgm, const char *name) {
    ClientGroup *cg = cgm_get(cgm, name);
    if (!cg) return -1;
    if (cg->sender_pid   > 0) kill(cg->sender_pid,   SIGKILL);
    if (cg->receiver_pid > 0) kill(cg->receiver_pid, SIGKILL);
    return hash_remove(cgm->groups, name, free);
}

int cgm_exists(ClientGroupsMng *cgm, const char *name) {
    return hash_lookup(cgm->groups, name) != NULL;
}

static void _kill_all_cb(const char *k, void *v, void *arg) {
    ClientGroup *cg = (ClientGroup *)v;
    (void)k;
    (void)arg;
    if (cg->sender_pid   > 0) kill(cg->sender_pid,   SIGKILL);
    if (cg->receiver_pid > 0) kill(cg->receiver_pid, SIGKILL);
}

void cgm_remove_all(ClientGroupsMng *cgm) {
    if (!cgm) return;
    hash_foreach(cgm->groups, _kill_all_cb, NULL);
    hash_destroy(cgm->groups, free);
    cgm->groups = hash_create();
}