#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

void count_words(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file for word counting");
        exit(1);
    }

    int words = 0;
    char ch, prev_ch = ' ';
    while ((ch = fgetc(file)) != EOF) {
        // Count a new word if we see a non-space character after a space
        if (!isspace(ch) && isspace(prev_ch)) {
            words++;
        }
        prev_ch = ch;
    }

    fclose(file);
    printf("Child 1: Total number of words = %d\n", words);
}

void invert_case(const char *filename) {
    FILE *file = fopen(filename, "r+"); // Open the file in read+write mode
    if (file == NULL) {
        perror("Failed to open file for case inversion");
        exit(1);
    }

    char ch;
    long pos;
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) {
            pos = ftell(file);                 // Get current position
            fseek(file, pos - 1, SEEK_SET);    // Move back to overwrite the character
            fputc(islower(ch) ? toupper(ch) : tolower(ch), file); // Invert case and write
            fseek(file, pos, SEEK_SET);        // Move back to the next character
        }
    }

    fclose(file);
    printf("Child 2: Inverted case of all alphabetic characters.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    pid_t pid1, pid2;

    // Create the first child process for word counting
    pid1 = fork();
    if (pid1 < 0) {
        perror("Failed to fork first child");
        return 1;
    } else if (pid1 == 0) {
        // First child process
        count_words(argv[1]);
        exit(0);
    }

    // Create the second child process for case inversion
    pid2 = fork();
    if (pid2 < 0) {
        perror("Failed to fork second child");
        return 1;
    } else if (pid2 == 0) {
        // Second child process
        invert_case(argv[1]);
        exit(0);
    }

    // Parent process waits for both children to complete
    wait(NULL); // Wait for the first child
    wait(NULL); // Wait for the second child

    printf("Parent: Both child processes completed.\n");

    return 0;
}
