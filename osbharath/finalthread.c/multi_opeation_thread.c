#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

#define ARRAY_SIZE 10
#define MATRIX_SIZE 3
#define STRING_SIZE 100
#define FILENAME "sample.txt"

// Shared resources
int numbers[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int matrix[MATRIX_SIZE][MATRIX_SIZE] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
char str[STRING_SIZE] = "Hello, World!";

// Function to calculate sum of array elements
void* sum_of_numbers(void* arg) {
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += numbers[i];
    }
    printf("Sum of numbers in array: %d\n", sum);
    return NULL;
}

// Function to calculate transpose of a matrix
void* transpose_matrix(void* arg) {
    int transpose[MATRIX_SIZE][MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            transpose[j][i] = matrix[i][j];
        }
    }
    printf("Transpose of the matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", transpose[i][j]);
        }
        printf("\n");
    }
    return NULL;
}

// Function to count words in a file
void* count_words_in_file(void* arg) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    int words = 0;
    char ch, prev_ch = ' ';
    while ((ch = fgetc(file)) != EOF) {
        if (!isspace(ch) && isspace(prev_ch)) {
            words++;
        }
        prev_ch = ch;
    }

    fclose(file);
    printf("Total number of words in the file: %d\n", words);
    return NULL;
}

// Function to reverse a string
void* reverse_string(void* arg) {
    char *s = (char *)arg;
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
    printf("Reversed string: %s\n", s);
    return NULL;
}

int main() {
    // Creating and initializing the sample file
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        perror("Failed to create sample file");
        return 1;
    }
    fprintf(file, "This is a sample file with some words to count.");
    fclose(file);

    pthread_t thread1, thread2, thread3, thread4;

    // Creating threads for each operation
    if (pthread_create(&thread1, NULL, sum_of_numbers, NULL) != 0) {
        perror("Failed to create thread for sum of numbers");
        return 1;
    }

    if (pthread_create(&thread2, NULL, transpose_matrix, NULL) != 0) {
        perror("Failed to create thread for matrix transpose");
        return 1;
    }

    if (pthread_create(&thread3, NULL, count_words_in_file, NULL) != 0) {
        perror("Failed to create thread for word count in file");
        return 1;
    }

    if (pthread_create(&thread4, NULL, reverse_string, str) != 0) {
        perror("Failed to create thread for string reversal");
        return 1;
    }

    // Wait for threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    printf("All operations completed.\n");
    return 0;
}
