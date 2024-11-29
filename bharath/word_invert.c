#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Get the filename from command line argument
    char *filename = argv[1];

    // Create first child process for counting words
    pid_t child1 = fork();
    if (child1 == 0) {
        // Child 1: Count total number of words
        FILE *inputFile = fopen(filename, "r");
        if (inputFile == NULL) {
            perror("Failed to open file");
            exit(1);
        }

        int count = 0;
        char word[100]; // Buffer to hold words
        while (fscanf(inputFile, "%s", word) != EOF) {
            count++;
        }

        fclose(inputFile);
        printf("Total number of words: %d\n", count);
        exit(0); // Exit child 1
    }

    // Create second child process for inverting case
    pid_t child2 = fork();
    if (child2 == 0) {
        // Child 2: Invert case of alphabets in the file
        FILE *inputFile = fopen(filename, "r");
        if (inputFile == NULL) {
            perror("Failed to open file");
            exit(1);
        }

        // Create output file
        FILE *outputFile = fopen("inverted_case.txt", "w");
        if (outputFile == NULL) {
            perror("Failed to create output file");
            fclose(inputFile);
            exit(1);
        }

        int ch;
        while ((ch = fgetc(inputFile)) != EOF) {
            if (isalpha(ch)) {
                // Invert case: use toupper() and tolower()
                ch = islower(ch) ? toupper(ch) : tolower(ch);
            }
            fputc(ch, outputFile);
        }

        fclose(inputFile);
        fclose(outputFile);
        exit(0); // Exit child 2
    }

    // Wait for both children to finish
    wait(NULL); // Wait for first child
    wait(NULL); // Wait for second child

    // Output to indicate completion
    printf("Both child processes have finished their tasks.\n");

    return 0;
}
