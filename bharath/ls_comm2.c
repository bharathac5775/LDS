#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Include this header for wait()

int main() {
    // Create a child process
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) executing 'ls' command...\n", getpid());
        
        // Execute the 'ls' command
        execlp("ls", "ls", NULL);
        
        // If execlp fails
        perror("execlp failed");
        exit(1);
    } else {
        // Parent process
        printf("Parent process (PID: %d) created child (PID: %d)\n", getpid(), pid);
        
        // Wait for the child process to finish
        wait(NULL);
        
        printf("Child process completed. Parent process exiting.\n");
    }

    return 0;
}
