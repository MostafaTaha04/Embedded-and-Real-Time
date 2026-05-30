#define _POSIX_C_SOURCE 200809L
#include "client_mng.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#define MQ_KEY  0xCAFE1234
#define MQ_TYPE 1L

typedef struct {
    long   mtype;
    pid_t  pid;
    char   role;
} MqPidMsg;

static char _last_msg[MAX_MSG_LEN] = "";

const char *client_mng_last_msg(ClientMng *cm) {
    (void)cm;
    return _last_msg;
}

static int _transact(ClientMng *cm, ClientRequest *req, ServerResponse *res) {
    if (client_net_send(cm->net, req) != 0)  return -1;
    if (client_net_recv(cm->net, res) != 0)  return -1;
    strncpy(_last_msg, res->message, MAX_MSG_LEN - 1);
    _last_msg[MAX_MSG_LEN - 1] = '\0';
    return 0;
}

ClientMng *client_mng_create(const char *server_ip) {
    ClientMng *cm = calloc(1, sizeof(ClientMng));
    if (!cm) return NULL;
    strncpy(cm->server_ip, server_ip, 15);
    cm->server_ip[15] = '\0';
    cm->net    = client_net_create(server_ip, SERVER_TCP_PORT);
    cm->groups = cgm_create();
    if (!cm->net || !cm->groups) {
        client_mng_destroy(cm);
        return NULL;
    }
    return cm;
}

void client_mng_destroy(ClientMng *cm) {
    if (!cm) return;
    cgm_destroy(cm->groups);
    client_net_destroy(cm->net);
    free(cm);
}

int client_mng_register(ClientMng *cm,
                         const char *user, const char *pass) {
    ClientRequest  req;
    ServerResponse res;
    memset(&req, 0, sizeof(req));
    memset(&res, 0, sizeof(res));
    req.type = MSG_REGISTER;
    strncpy(req.username, user, MAX_USERNAME_LEN - 1);
    strncpy(req.password, pass, MAX_PASSWORD_LEN - 1);
    if (_transact(cm, &req, &res) != 0) return -1;
    return (res.type == RES_OK) ? 0 : -1;
}

int client_mng_login(ClientMng *cm,
                      const char *user, const char *pass) {
    ClientRequest  req;
    ServerResponse res;
    memset(&req, 0, sizeof(req));
    memset(&res, 0, sizeof(res));
    req.type = MSG_LOGIN;
    strncpy(req.username, user, MAX_USERNAME_LEN - 1);
    strncpy(req.password, pass, MAX_PASSWORD_LEN - 1);
    if (_transact(cm, &req, &res) != 0) return -1;
    if (res.type == RES_OK) {
        strncpy(cm->username, user, MAX_USERNAME_LEN - 1);
        cm->logged_in = 1;
        return 0;
    }
    return -1;
}

int client_mng_logout(ClientMng *cm) {
    ClientRequest  req;
    ServerResponse res;
    memset(&req, 0, sizeof(req));
    memset(&res, 0, sizeof(res));
    req.type = MSG_LOGOUT;
    strncpy(req.username, cm->username, MAX_USERNAME_LEN - 1);
    cgm_remove_all(cm->groups);
    if (_transact(cm, &req, &res) != 0) return -1;
    cm->logged_in = 0;
    memset(cm->username, 0, sizeof(cm->username));
    return (res.type == RES_OK) ? 0 : -1;
}

static int _open_group_windows(ClientMng *cm, const char *gname,
                                const char *mc_ip, int mc_port) {
    int      mq_id;
    char     cmd[512];
    pid_t    spid = -1;
    pid_t    rpid = -1;
    int      i;
    MqPidMsg msg;

    mq_id = msgget(MQ_KEY, IPC_CREAT | 0666);
    if (mq_id < 0) { perror("msgget"); return -1; }

    snprintf(cmd, sizeof(cmd),
        "gnome-terminal --title='SEND:%s' -- ./mc_sender %s %d %d &",
        gname, mc_ip, mc_port, mq_id);
    system(cmd);

    snprintf(cmd, sizeof(cmd),
        "gnome-terminal --title='RECV:%s' -- ./mc_receiver %s %d %d &",
        gname, mc_ip, mc_port, mq_id);
    system(cmd);

    for (i = 0; i < 2; i++) {
        if (msgrcv(mq_id, &msg, sizeof(msg) - sizeof(long),
                   MQ_TYPE, 0) < 0) {
            perror("msgrcv");
            break;
        }
        if (msg.role == 'S') spid = msg.pid;
        else                  rpid = msg.pid;
    }
    msgctl(mq_id, IPC_RMID, NULL);
    cgm_add(cm->groups, gname, mc_ip, mc_port, spid, rpid);
    return 0;
}

int client_mng_create_group(ClientMng *cm, const char *gname) {
    ClientRequest  req;
    ServerResponse res;
    memset(&req, 0, sizeof(req));
    memset(&res, 0, sizeof(res));
    req.type = MSG_CREATE_GROUP;
    strncpy(req.username,   cm->username, MAX_USERNAME_LEN - 1);
    strncpy(req.group_name, gname,        MAX_GROUP_NAME_LEN - 1);
    if (_transact(cm, &req, &res) != 0) return -1;
    if (res.type != RES_GROUP_INFO) return -1;
    return _open_group_windows(cm, gname,
                                res.multicast_ip, res.multicast_port);
}

int client_mng_join_group(ClientMng *cm, const char *gname) {
    ClientRequest  req;
    ServerResponse res;
    memset(&req, 0, sizeof(req));
    memset(&res, 0, sizeof(res));
    req.type = MSG_JOIN_GROUP;
    strncpy(req.username,   cm->username, MAX_USERNAME_LEN - 1);
    strncpy(req.group_name, gname,        MAX_GROUP_NAME_LEN - 1);
    if (_transact(cm, &req, &res) != 0) return -1;
    if (res.type != RES_GROUP_INFO) return -1;
    return _open_group_windows(cm, gname,
                                res.multicast_ip, res.multicast_port);
}

int client_mng_leave_group(ClientMng *cm, const char *gname) {
    ClientRequest  req;
    ServerResponse res;
    memset(&req, 0, sizeof(req));
    memset(&res, 0, sizeof(res));
    req.type = MSG_LEAVE_GROUP;
    strncpy(req.username,   cm->username, MAX_USERNAME_LEN - 1);
    strncpy(req.group_name, gname,        MAX_GROUP_NAME_LEN - 1);
    if (_transact(cm, &req, &res) != 0) return -1;
    if (res.type != RES_OK) return -1;
    cgm_remove(cm->groups, gname);
    return 0;
}

void client_mng_exit(ClientMng *cm) {
    ClientRequest  req;
    ServerResponse res;
    memset(&req, 0, sizeof(req));
    memset(&res, 0, sizeof(res));
    req.type = MSG_EXIT;
    strncpy(req.username, cm->username, MAX_USERNAME_LEN - 1);
    cgm_remove_all(cm->groups);
    _transact(cm, &req, &res);
    client_net_destroy(cm->net);
    cm->net = NULL;
}