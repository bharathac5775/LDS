// odd_series.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void generate_odd_series(int n) {
    printf("Parent process: Generating odd series up to %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", 2 * i + 1); // Generates 1, 3, 5, 7, ...
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of terms>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); // Convert the command-line argument to integer
    if (n < 1) {
        fprintf(stderr, "The number of terms must be a positive integer.\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process: Execute even_series.c with `exec()`
        printf("Child process: Executing even_series program.\n");
        execl("./C_even_exec", "./C_even_exec", argv[1], NULL); // Pass `n` to the child program
        perror("execl failed"); // If execl fails
        exit(1);
    } else {
        // Parent process: Generate odd series
        generate_odd_series(n);
        wait(NULL); // Wait for the child process to complete
    }

    return 0;
}
