#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <string.h>

void* count_words(void* arg) {
    char *filename = (char *)arg;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
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
    printf("Total number of words: %d\n", words);
    return NULL;
}

void* to_lowercase(void* arg) {
    char *filename = (char *)arg;
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    char ch;
    long pos;
    while ((ch = fgetc(file)) != EOF) {
        if (isupper(ch)) {
            pos = ftell(file);
            fseek(file, pos-1, SEEK_SET);
            fputc(tolower(ch), file);
            fseek(file, pos , SEEK_SET);
        }
    }

    fclose(file);
    printf("Converted uppercase letters to lowercase.\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, count_words, argv[1]) != 0) {
        perror("Failed to create word-counting thread");
        return 1;
    }

    if (pthread_create(&thread2, NULL, to_lowercase, argv[1]) != 0) {
        perror("Failed to create case-conversion thread");
        return 1;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both operations completed.\n");
    return 0;
}
