#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create a new process

    if (pid < 0) {
        // fork failed
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // This is the child process
        printf("Child: Executing 'ls' command\n");
        execlp("ls", "ls", NULL);  // Replace the child process with "ls" command
        perror("execlp failed");   // If execlp fails, print an error
    } else {
        // This is the parent process
        printf("Parent: Waiting for child to complete...\n");
       // wait(NULL);  // Parent waits for the child process to finish
        printf("Parent: Child completed. Now parent continues.\n");
    }

    return 0;
}
