#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>    
#include <sys/types.h>   
#include <sys/wait.h>    

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];
    pid_t pid;
    int status;

    printf("--- Simple Custom Shell Started ---\n");
    printf("Type 'exit' to quit.\n\n");

    /* The shell runs in an infinite loop */
    while (1) {
        printf("MyShell> ");
        fflush(stdout);

        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            printf("\nExiting shell...\n");
            break;
        }
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            continue;
        }

        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (strcmp(args[0], "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }

        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } 
        else if (pid == 0) {
            /* CHILD PROCESS */
            if (execvp(args[0], args) == -1) {
                perror("Command execution failed");
            }
            exit(1);
        } 
        else {
            /* PARENT PROCESS (The Shell) */
            /* Wait for the child process to complete */
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}