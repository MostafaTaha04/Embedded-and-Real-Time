#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;

    printf("--- Signal Exercise (Parent/Child) ---\n");
    
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        /* --- Child Process --- */
        while (1) {
            printf("in child\n");
            sleep(1); /* We sleep for 1 second so it doesn't crash your terminal with a flood of text */
        }
    } 
    else {
        /* --- Parent (Father) Process --- */
        printf("Father: Created child with PID %d\n", pid);
        printf("Father: Sleeping for 10 seconds...\n\n");
        
        sleep(10);
        
        printf("\nFather: Woke up! Sending SIGTERM to child...\n");
        
        /* kill() sends a signal to a process. 
           SIGTERM (15) is the standard termination signal[cite: 1005, 1058]. */
        if (kill(pid, SIGTERM) == 0) {
            printf("Father: Signal sent successfully.\n");
        } else {
            perror("Father: Failed to send signal");
        }

        /* Wait for the child to properly terminate so it doesn't become a "zombie" process */
        wait(NULL);
        printf("Father: Child has been terminated. Exiting.\n");
    }

    return 0;
}