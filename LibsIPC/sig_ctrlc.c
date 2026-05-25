/* MUST BE LINE 1: Force POSIX features before strict ANSI hides them */
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h> /* Now struct sigaction will be visible [cite: 1212, 1257] */

volatile sig_atomic_t ctrl_c_count = 0;

void handle_sigint(int sig) {
    (void)sig;
    ctrl_c_count++;
    printf("\n[Caught Ctrl-C! Strike %d of 3]\n", ctrl_c_count);

    if (ctrl_c_count >= 3) {
        printf("That's 3 strikes! Exiting gracefully...\n");
        exit(0);
    }
}

int main(void) {
    /* In C90, ALL variables must be declared before any executable code */
    struct sigaction sa;

    /* Set up the sigaction structure [cite: 1285, 1286, 1287, 1288] */
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; 

    /* Register the signal handler for SIGINT */
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Failed to register signal handler");
        return 1;
    }

    printf("--- 3-Strike Ctrl-C Catcher ---\n");
    printf("Try to stop me by pressing Ctrl-C in your terminal!\n\n");

    /* Endless loop printing '*' */
    while (1) {
        printf("*");
        fflush(stdout); 
        sleep(1);       
    }

    return 0;
}