#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int i;

    // Array of commands and their arguments
    char *commands[][4] = {
        {"ls", NULL},
        {"ls", "-l", NULL},
        {"pwd", NULL},
        {"date", NULL}
    };

    // Loop to create 4 child processes
    for (i = 0; i < 4; i++) {
        pid = fork();

        if (pid < 0) {
            // fork failed
            perror("fork failed");
            return 1;
        } else if (pid == 0) {
            // This is the child process
            printf("Child %d: Executing %s command\n", i + 1, commands[i][0]);
            execlp(commands[i][0], commands[i][0], commands[i][1], NULL);  // Execute command
            perror("execlp failed");  // If execlp fails, print an error
            return 1;  // Exit the child process if execlp fails
        }
    }

    // Parent process waits for all child processes to complete
    for (i = 0; i < 4; i++) {
        wait(NULL);  // Wait for each child process to finish
    }

    printf("Parent: All children completed.\n");
    return 0;
}
