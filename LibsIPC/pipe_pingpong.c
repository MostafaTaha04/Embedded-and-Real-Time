#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    /* p1 is Parent->Child, p2 is Child->Parent */
    int p1[2], p2[2];
    pid_t pid;
    char buf[50];

    /* Create both pipes */
    if (pipe(p1) < 0 || pipe(p2) < 0) {
        perror("Pipe creation failed");
        exit(1);
    }

    pid = fork();

    if (pid > 0) {
        /* --- Parent Process --- */
        close(p1[0]); /* Close read end of p1 */
        close(p2[1]); /* Close write end of p2 */

        /* 1. Parent writes Ping */
        write(p1[1], "Ping", 5);
        
        /* 4. Parent reads Pong */
        read(p2[0], buf, sizeof(buf));
        printf("Parent received: %s\n", buf);

        close(p1[1]);
        close(p2[0]);
        wait(NULL); /* Wait for child to finish */
    } 
    else if (pid == 0) {
        /* --- Child Process --- */
        close(p1[1]); /* Close write end of p1 */
        close(p2[0]); /* Close read end of p2 */

        /* 2. Child reads Ping */
        read(p1[0], buf, sizeof(buf));
        printf("Child received:  %s\n", buf);

        /* 3. Child writes Pong */
        write(p2[1], "Pong", 5);

        close(p1[0]);
        close(p2[1]);
    }

    return 0;
}