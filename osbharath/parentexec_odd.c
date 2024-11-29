#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
        printf("Child process: Executing even_series program.\n");
        execlp("./child_even","./child_even",argv[1],NULL);
        perror("execl failed"); // If execl fails
        exit(1);
        
    } else {
        // Parent process
        generate_odd_series(n);
        wait(NULL); // Wait for the child process to complete
    }

    return 0;
}
