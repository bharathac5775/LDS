#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Size of the buffer
#define NUM_ITEMS 10   // Total items to be produced and consumed

// Shared buffer
int buffer[BUFFER_SIZE];
int in = 0;  // Index for next producer to insert item
int out = 0; // Index for next consumer to remove item

// Semaphores for synchronization
sem_t empty;  // Keeps track of empty slots in the buffer
sem_t full;   // Keeps track of full slots in the buffer
pthread_mutex_t mutex; // Mutex to protect the critical section

// Function for the producer thread
void* producer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&empty);  // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Enter critical section

        // Produce an item and add it to the buffer
        buffer[in] = i;
        printf("Producer produced item: %d at index %d\n", i, in);
        in = (in + 1) % BUFFER_SIZE; // Move to the next position

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full);  // Signal that there's a new item to consume
        sleep(rand() % 2);  // Simulate some time taken to produce
    }

    return NULL;
}

// Function for the consumer thread
void* consumer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full);  // Wait for a full slot
        pthread_mutex_lock(&mutex); // Enter critical section

        // Consume an item from the buffer
        int item = buffer[out];
        printf("Consumer consumed item: %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE; // Move to the next position

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty);  // Signal that there's an empty slot
        sleep(rand() % 2);  // Simulate some time taken to consume
    }

    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize the semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, all buffer slots are empty
    sem_init(&full, 0, 0);            // Initially, no item is in the buffer
    pthread_mutex_init(&mutex, NULL);  // Initialize the mutex

    // Create the producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for the threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy the semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
