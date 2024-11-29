#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void generate_fibonacci(int n) {
    int first = 1, second = 1, next;
    printf("Fibonacci Series up to %d terms:\n", n);

    // Print the first two terms
    printf("%d, %d", first, second);

    for (int i = 3; i <= n; i++) { // Start from the 3rd term since 1st and 2nd are already printed
        next = first + second;
        printf(", %d", next);
        first = second;
        second = next;
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) { // Check if exactly one argument (n) is provided
        fprintf(stderr, "Usage: %s <number of terms>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); // Convert the command-line argument to an integer
    if (n < 1) { // Validate that n is a positive integer
        fprintf(stderr, "The number of terms must be a positive integer.\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) { // Error in fork()
        perror("Fork failed");
        return 1;
    } else if (pid == 0) { // Child process
        printf("Child process (PID: %d): Generating Fibonacci series.\n", getpid());
        generate_fibonacci(n); // Generate and print the Fibonacci series
        exit(0); // Exit after finishing the task
    } else { // Parent process
        wait(NULL); // Wait for the child process to complete
        printf("Parent process (PID: %d): Child has finished execution.\n", getpid());
    }

    return 0;
}
