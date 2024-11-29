#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

// Circular buffer
int buffer[BUFFER_SIZE];
int in = 0;   // Index for producer
int out = 0;  // Index for consumer
int count = 0; // Number of items in buffer

// Mutex and condition variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;

// Shared counter
int total_items = 0;

// Producer function
void *producer(void *arg) {
    for (int i = 1; i <= NUM_ITEMS; i++) {
        // Lock mutex before modifying the buffer
        pthread_mutex_lock(&mutex);

        // Wait if the buffer is full
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&not_full, &mutex);
        }

        // Add an item to the buffer
        buffer[in] = i;
        printf("Producer: Produced item %d at index %d\n", i, in);
        in = (in + 1) % BUFFER_SIZE;
        count++;
        total_items++;
        printf("Counter: Total items in buffer: %d\n", count);

        // Signal the consumer that the buffer is not empty
        pthread_cond_signal(&not_empty);

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Simulate work
        usleep(rand() % 500000);
    }
    return NULL;
}

// Consumer function
void *consumer(void *arg) {
    for (int i = 1; i <= NUM_ITEMS; i++) {
        // Lock mutex before modifying the buffer
        pthread_mutex_lock(&mutex);

        // Wait if the buffer is empty
        while (count == 0) {
            pthread_cond_wait(&not_empty, &mutex);
        }

        // Remove an item from the buffer
        int item = buffer[out];
        printf("Consumer: Consumed item %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
        count--;
        total_items--;
        printf("Counter: Total items in buffer: %d\n", count);

        // Signal the producer that the buffer is not full
        pthread_cond_signal(&not_full);

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Simulate work
        usleep(rand() % 500000);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize random seed
    srand(time(NULL));

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    printf("All items produced and consumed.\n");

    // Clean up
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);

    return 0;
}
