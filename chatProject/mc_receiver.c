#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <netinet/in.h>

#define MAX_MSG 512

typedef struct {
    long  mtype;
    pid_t pid;
    char  role;
} MqPidMsg;

int main(int argc, char *argv[]) {
    int                sock;
    int                reuse = 1;
    int                n;
    struct sockaddr_in addr;
    struct sockaddr_in src;
    struct ip_mreq     mreq;
    socklen_t          slen;
    char               buf[MAX_MSG];
    MqPidMsg           m;
    const char        *mc_ip;
    int                port;
    int                mq_id;

    if (argc < 4) {
        fprintf(stderr, "Usage: mc_receiver <mc_ip> <port> <mq_id>\n");
        return 1;
    }

    mc_ip = argv[1];
    port  = atoi(argv[2]);
    mq_id = atoi(argv[3]);

    m.mtype = 1L;
    m.pid   = getpid();
    m.role  = 'R';
    msgsnd(mq_id, &m, sizeof(m) - sizeof(long), 0);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); return 1; }

    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(port);

    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return 1;
    }

    memset(&mreq, 0, sizeof(mreq));
    inet_pton(AF_INET, mc_ip, &mreq.imr_multiaddr);
    mreq.imr_interface.s_addr = INADDR_ANY;
    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

    printf("[RECEIVER] Listening on %s:%d\n", mc_ip, port);
    while (1) {
        slen = sizeof(src);
        memset(&src, 0, sizeof(src));
        n = recvfrom(sock, buf, sizeof(buf) - 1, 0,
                     (struct sockaddr *)&src, &slen);
        if (n < 0) break;
        buf[n] = '\0';
        printf("[%s] %s\n", inet_ntoa(src.sin_addr), buf);
        fflush(stdout);
    }
    close(sock);
    return 0;
}