#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

void convert_to_uppercase(const char *filename) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Failed to open file for uppercase conversion");
        exit(EXIT_FAILURE);
    }

    int ch;
    long pos;
    while ((ch = fgetc(file)) != EOF) {
        pos = ftell(file) - 1; // Get the position of the current character
        if (islower(ch)) {
            fseek(file, pos, SEEK_SET); // Move to the position
            fputc(toupper(ch), file);   // Convert to uppercase
        }
    }
    fclose(file);
}

void count_a_characters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file for counting 'a's");
        exit(EXIT_FAILURE);
    }

    int ch;
    int count = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == 'a' || ch == 'A') {
            count++;
        }
    }
    fclose(file);
    printf("Total number of 'a' characters: %d\n", count);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    pid_t pid1, pid2;

    // Create first child to convert lowercase to uppercase
    if ((pid1 = fork()) == 0) {
        convert_to_uppercase(filename);
        exit(0);
    } else if (pid1 < 0) {
        perror("Fork failed");
        return EXIT_FAILURE;
    }

    // Create second child to count 'a' characters
    if ((pid2 = fork()) == 0) {
        count_a_characters(filename);
        exit(0);
    } else if (pid2 < 0) {
        perror("Fork failed");
        return EXIT_FAILURE;
    }

    // Wait for both children to finish
    wait(NULL);
    wait(NULL);

    printf("Both children have finished processing the file.\n");
    return EXIT_SUCCESS;
}
