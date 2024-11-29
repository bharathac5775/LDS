#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10

// Global array
int numbers[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Function to calculate the sum of the array
void* calculate_sum(void* arg) {
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += numbers[i];
    }
    printf("Sum of the array: %d\n", sum);
    return NULL;
}

// Function to count even numbers in the array
void* count_even(void* arg) {
    int count = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (numbers[i] % 2 == 0) {
            count++;
        }
    }
    printf("Count of even numbers: %d\n", count);
    return NULL;
}

// Function to reverse the array
void* reverse_array(void* arg) {
    for (int i = 0; i < ARRAY_SIZE / 2; i++) {
        int temp = numbers[i];
        numbers[i] = numbers[ARRAY_SIZE - 1 - i];
        numbers[ARRAY_SIZE - 1 - i] = temp;
    }
    printf("Reversed array: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;

    // Create threads for different computations
    if (pthread_create(&thread1, NULL, calculate_sum, NULL) != 0) {
        perror("Failed to create thread for sum calculation");
        return 1;
    }
    
    if (pthread_create(&thread2, NULL, count_even, NULL) != 0) {
        perror("Failed to create thread for counting even numbers");
        return 1;
    }

    if (pthread_create(&thread3, NULL, reverse_array, NULL) != 0) {
        perror("Failed to create thread for reversing array");
        return 1;
    }

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("All computations completed.\n");
    return 0;
}
