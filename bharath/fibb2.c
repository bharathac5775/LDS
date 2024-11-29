#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // Check if the number of arguments is correct
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return 1;
    }

    // Convert the argument to an integer
    int n = atoi(argv[1]);

    // Check if the input is a nonnegative integer
    if (n <= 0) {
        fprintf(stderr, "Error: Please enter a positive integer.\n");
        return 1;
    }

    // Create a child process
    pid_t pid = fork();

    if (pid < 0) {
        // If fork() fails
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process: Generate Fibonacci sequence
        printf("Child process: Fibonacci sequence up to %d terms:\n", n);

        // Generate Fibonacci sequence
        int a = 0, b = 1, next;
        for (int i = 1; i <= n; i++) {
            printf("%d ", a);
            next = a + b;
            a = b;
            b = next;
        }
        printf("\n");

        exit(0); // Child process exits
    } else {
        // Parent process: wait for child to finish
        wait(NULL);
        printf("Parent process: Child process has completed.\n");
    }

    return 0;
}
