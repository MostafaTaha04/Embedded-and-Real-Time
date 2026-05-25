#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <sys/wait.h>

int main(void) {
    mqd_t mq_ping, mq_pong;
    pid_t pid;
    char buf[50];
    struct mq_attr attr;

    /* Setup queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 50;
    attr.mq_curmsgs = 0;

    /* Unlink any leftover queues from previous crashed runs */
    mq_unlink("/ping_q");
    mq_unlink("/pong_q");

    /* Open queues. O_CREAT creates it if it doesn't exist */
    mq_ping = mq_open("/ping_q", O_RDWR | O_CREAT, 0660, &attr);
    mq_pong = mq_open("/pong_q", O_RDWR | O_CREAT, 0660, &attr);

    if (mq_ping == (mqd_t)-1 || mq_pong == (mqd_t)-1) {
        perror("Failed to create message queues");
        exit(1);
    }

    pid = fork();

    if (pid > 0) {
        /* --- Parent Process --- */
        
        /* 1. Parent sends Ping */
        mq_send(mq_ping, "Ping", 5, 0);
        
        /* 4. Parent receives Pong */
        mq_receive(mq_pong, buf, 50, NULL);
        printf("Parent received: %s\n", buf);

        wait(NULL);

        /* Close and remove queues from the OS */
        mq_close(mq_ping);
        mq_close(mq_pong);
        mq_unlink("/ping_q");
        mq_unlink("/pong_q");
    } 
    else if (pid == 0) {
        /* --- Child Process --- */
        
        /* 2. Child receives Ping */
        mq_receive(mq_ping, buf, 50, NULL);
        printf("Child received:  %s\n", buf);

        /* 3. Child sends Pong */
        mq_send(mq_pong, "Pong", 5, 0);

        mq_close(mq_ping);
        mq_close(mq_pong);
    }

    return 0;
}
