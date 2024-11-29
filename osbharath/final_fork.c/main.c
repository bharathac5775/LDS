#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_child(const char *program_name, const char *arg) {
    if (fork() == 0) {
        // In child process
        if (arg) {
            execlp(program_name, program_name, arg, (char *)NULL);
        } else {
            execlp(program_name, program_name, (char *)NULL);
        }
        // If exec fails
        perror("exec failed");
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Execute the matrix sum program
    execute_child("./matrix_sum", NULL);

    // Execute the change case program
    execute_child("./change_case", NULL);

    // Execute the count character occurrences program
    execute_child("./count_char", NULL);

    // Execute the sum of digits program
    execute_child("./sum_of_digits", NULL);

    // Execute the count words in file program
    execute_child("./count_words", "sample.txt"); // Replace "sample.txt" with your file name

    // Execute the count whitespace in file program
    execute_child("./count_whitespace", "sample.txt"); // Replace "sample.txt" with your file name

    // Wait for all child processes to finish
    while (wait(NULL) > 0);

    printf("All child processes completed.\n");
    return 0;
}
