#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

char *filename; // Declare a global variable for the filename

// Function to count the number of words in the file
void *count_words(void *arg) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file for counting words");
        pthread_exit(NULL);
    }

    int word_count = 0;
    char ch, prev_char = ' ';
    while ((ch = fgetc(file)) != EOF) {
        // Count words by identifying spaces or newlines between words
        if (isspace(ch) && !isspace(prev_char)) {
            word_count++;
        }
        prev_char = ch;
    }

    // Count the last word if the file doesn't end with whitespace
    if (!isspace(prev_char)) {
        word_count++;
    }

    fclose(file);
    printf("Total number of words: %d\n", word_count);
    pthread_exit(NULL);
}

// Function to convert all uppercase characters to lowercase in the file
void *convert_to_lowercase(void *arg) {
    FILE *file = fopen(filename, "r+"); // Open file for reading and writing
    if (!file) {
        perror("Error opening file for case conversion");
        pthread_exit(NULL);
    }

    char ch;
    long position;

    while ((ch = fgetc(file)) != EOF) {
        // Convert uppercase letters to lowercase
        if (isupper(ch)) {
            position = ftell(file); // Get current position
            fseek(file, position - 1, SEEK_SET); // Move back to character position
            fputc(tolower(ch), file); // Write lowercase character
            fseek(file, position, SEEK_SET); // Return to reading position
        }
    }

    fclose(file);
    printf("Uppercase letters converted to lowercase.\n");
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Get the filename from command line arguments
    filename = argv[1];

    pthread_t thread1, thread2;

    // Create thread to count words
    if (pthread_create(&thread1, NULL, count_words, NULL) != 0) {
        perror("Failed to create word count thread");
        return 1;
    }

    // Create thread to convert uppercase letters to lowercase
    if (pthread_create(&thread2, NULL, convert_to_lowercase, NULL) != 0) {
        perror("Failed to create case conversion thread");
        return 1;
    }

    // Wait for both threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads have completed their tasks.\n");

    return 0;
}
