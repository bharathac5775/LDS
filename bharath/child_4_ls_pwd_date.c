#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    
    // Array of commands with variable arguments
    char *commands[4][3] = {
        {"ls", "ls", NULL},           // Command 1: ls
        {"ls", "ls", "-l"},           // Command 2: ls -l
        {"pwd", "pwd", NULL},         // Command 3: pwd
        {"date", "date", NULL}        // Command 4: date
    };

    // Create four child processes
    for (int i = 0; i < 4; i++) {
        pid = fork();
        
        if (pid < 0) {
            // If fork() fails
            perror("fork failed");
            return 1;
        } else if (pid == 0) {
            // In the child process, execute the corresponding command
            printf("Child %d: Executing %s command\n", i + 1, commands[i][0]);
            
            // Execute the command with variable arguments
            if (commands[i][2] != NULL) {
                execlp(commands[i][0], commands[i][1], commands[i][2], NULL);
            } else {
                execlp(commands[i][0], commands[i][1], NULL);
            }
            
            perror("execlp failed");  // If execlp fails, print an error
            exit(1);  // Exit if execlp fails
        }
    }

    // Parent process waits for all children to finish
    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    printf("Parent: All child processes have completed.\n");

    return 0;
}
