#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Include for wait()

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Get the filename from command line argument
    char *filename = argv[1];

    // Create first child process for counting lines
    pid_t child1 = fork();
    if (child1 == 0) {
        // Child 1: Count lines
        execlp("wc", "wc", "-l", filename, NULL); // Use filename instead of sample
        perror("execlp failed"); // This will execute only if execlp fails
        exit(1);
    }

    // Create second child process for counting characters
    pid_t child2 = fork();
    if (child2 == 0) {
        // Child 2: Count characters
        execlp("wc", "wc", "-c", filename, NULL); // Use filename instead of sample
        perror("execlp failed"); // This will execute only if execlp fails
        exit(1);
    }

    // Wait for both children to finish
    wait(NULL); // Wait for first child
    wait(NULL); // Wait for second child

    // Output to indicate completion
    printf("Both child processes have finished counting.\n");

    return 0;
}
