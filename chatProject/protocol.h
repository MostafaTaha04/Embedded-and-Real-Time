#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#define MAX_USERNAME_LEN   32
#define MAX_PASSWORD_LEN   32
#define MAX_GROUP_NAME_LEN 32
#define MAX_MSG_LEN        512
#define MULTICAST_PORT_BASE 5000
#define SERVER_TCP_PORT     8080
#define MULTICAST_TTL       1

/* ─── Message Types (Client → Server) ─── */
typedef enum {
    MSG_REGISTER        = 1,
    MSG_LOGIN           = 2,
    MSG_LOGOUT          = 3,
    MSG_CREATE_GROUP    = 4,
    MSG_JOIN_GROUP      = 5,
    MSG_LEAVE_GROUP     = 6,
    MSG_EXIT            = 7
} ClientMsgType;

/* ─── Message Types (Server → Client) ─── */
typedef enum {
    RES_OK              = 100,
    RES_ERROR           = 101,
    RES_GROUP_INFO      = 102
} ServerMsgType;

/* ─── Generic Request (Client → Server) ─── */
typedef struct {
    ClientMsgType type;
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char group_name[MAX_GROUP_NAME_LEN];
} ClientRequest;

/* ─── Generic Response (Server → Client) ─── */
typedef struct {
    ServerMsgType type;
    char message[MAX_MSG_LEN];       /* error or status text  */
    char multicast_ip[16];           /* e.g. "239.1.2.3"      */
    int  multicast_port;             /* UDP port for the group */
} ServerResponse;

#endif /* PROTOCOL_H */