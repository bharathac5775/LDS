#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void generate_odd_series(int n) {
    printf("Odd Series: ");
    for (int i = 1; i < n * 2; i += 2) {
        printf("%d ", i);
    }
    printf("\n");
}

void generate_even_series(int n) {
    printf("Even Series: ");
    for (int i = 0; i < n * 2; i += 2) {
        printf("%d ", i);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Please provide a positive integer for n.\n");
        return 1;
    }

    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        generate_even_series(n);
    } else {
        // Parent process
        generate_odd_series(n);
        wait(NULL); // Wait for the child process to complete
    }

    return 0;
}
