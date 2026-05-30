#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define MAX_MSG 512

typedef struct {
    long  mtype;
    pid_t pid;
    char  role;
} MqPidMsg;

int main(int argc, char *argv[]) {
    int                sock;
    unsigned char      ttl = 1;
    struct sockaddr_in dest;
    char               buf[MAX_MSG];
    MqPidMsg           m;
    const char        *mc_ip;
    int                port;
    int                mq_id;

    if (argc < 4) {
        fprintf(stderr, "Usage: mc_sender <mc_ip> <port> <mq_id>\n");
        return 1;
    }

    mc_ip = argv[1];
    port  = atoi(argv[2]);
    mq_id = atoi(argv[3]);

    m.mtype = 1L;
    m.pid   = getpid();
    m.role  = 'S';
    msgsnd(mq_id, &m, sizeof(m) - sizeof(long), 0);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); return 1; }

    setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl));

    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port   = htons(port);
    inet_pton(AF_INET, mc_ip, &dest.sin_addr);

    printf("[SENDER] Connected to %s:%d - type messages:\n", mc_ip, port);
    while (fgets(buf, sizeof(buf), stdin)) {
        buf[strcspn(buf, "\n")] = '\0';
        if (strlen(buf) == 0) continue;
        sendto(sock, buf, strlen(buf), 0,
               (struct sockaddr *)&dest, sizeof(dest));
    }
    close(sock);
    return 0;
}