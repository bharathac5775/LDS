#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function for the first thread
void* thread_one_function(void* arg) {
    printf("This is thread one\n");
    return NULL;
}

// Function for the second thread
void* thread_two_function(void* arg) {
    printf("This is thread two\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2; // Declare thread identifiers

    // Create the first thread
    if (pthread_create(&thread1, NULL, thread_one_function, NULL) != 0) {
        perror("Failed to create thread one");
        return 1;
    }

    // Create the second thread
    if (pthread_create(&thread2, NULL, thread_two_function, NULL) != 0) {
        perror("Failed to create thread two");
        return 1;
    }

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads have finished executing.\n");
    return 0;
}
