#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256

// Global variable to hold the word count
int word_count = 0;
pthread_mutex_t count_mutex;

// Function to count words in the file
void* count_words(void* filename) {
    FILE* file = fopen((char*)filename, "r");
    if (file == NULL) {
        perror("Failed to open file for counting words");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, " \n");
        while (token != NULL) {
            pthread_mutex_lock(&count_mutex);
            word_count++;
            pthread_mutex_unlock(&count_mutex);
            token = strtok(NULL, " \n");
        }
    }
    fclose(file);
    return NULL;
}

// Function to change uppercase characters to lowercase
void* to_lowercase(void* filename) {
    FILE* file = fopen((char*)filename, "r+");
    if (file == NULL) {
        perror("Failed to open file for converting to lowercase");
        return NULL;
    }

    char ch;
    long position;
    while ((ch = fgetc(file)) != EOF) {
        position = ftell(file);
        if (isupper(ch)) {
            fseek(file, position - 1, SEEK_SET);
            fputc(tolower(ch), file);
            fseek(file, position, SEEK_SET); // Move back to the next character
        }
    }
    fclose(file);
    return NULL;
}

// Function to append a message to the file
void* append_message(void* filename) {
    FILE* file = fopen((char*)filename, "a");
    if (file == NULL) {
        perror("Failed to open file for appending message");
        return NULL;
    }

    fprintf(file, "\nThree threads have visited this file.\n");
    fclose(file);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pthread_t thread1, thread2, thread3;
    pthread_mutex_init(&count_mutex, NULL);

    // Create thread to count words
    if (pthread_create(&thread1, NULL, count_words, argv[1]) != 0) {
        perror("Failed to create thread for counting words");
        return EXIT_FAILURE;
    }

    // Create thread to convert to lowercase
    if (pthread_create(&thread2, NULL, to_lowercase, argv[1]) != 0) {
        perror("Failed to create thread for converting to lowercase");
        return EXIT_FAILURE;
    }

    // Create thread to append message
    if (pthread_create(&thread3, NULL, append_message, argv[1]) != 0) {
        perror("Failed to create thread for appending message");
        return EXIT_FAILURE;
    }

    // Wait for all threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // Print the total word count
    printf("Total number of words: %d\n", word_count);

    pthread_mutex_destroy(&count_mutex);
    return EXIT_SUCCESS;
}
