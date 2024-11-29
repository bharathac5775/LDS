#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5  // Size of the circular buffer

int buffer[BUFFER_SIZE];
int front = 0, rear = 0; // Pointers for the circular buffer

sem_t empty_slots; // Semaphore to track empty slots
sem_t filled_slots; // Semaphore to track filled slots
pthread_mutex_t mutex; // Mutex to protect the buffer

// Function to produce an item (Producer)
void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) { // Produces 10 items
        item = rand() % 100; // Generate a random item

        sem_wait(&empty_slots); // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Lock the buffer

        // Add the item to the buffer
        buffer[rear] = item;
        rear = (rear + 1) % BUFFER_SIZE;
        printf("Producer produced: %d\n", item);

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&filled_slots); // Signal that a slot is filled

        sleep(1); // Simulate production delay
    }
    return NULL;
}

// Function to consume an item (Consumer)
void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) { // Consumes 10 items
        sem_wait(&filled_slots); // Wait for a filled slot
        pthread_mutex_lock(&mutex); // Lock the buffer

        // Remove the item from the buffer
        item = buffer[front];
        front = (front + 1) % BUFFER_SIZE;
        printf("Consumer consumed: %d\n", item);

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty_slots); // Signal that a slot is empty

        sleep(2); // Simulate consumption delay
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores and mutex
    sem_init(&empty_slots, 0, BUFFER_SIZE); // Initially, all slots are empty
    sem_init(&filled_slots, 0, 0); // Initially, no slots are filled
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Clean up
    sem_destroy(&empty_slots);
    sem_destroy(&filled_slots);
    pthread_mutex_destroy(&mutex);

    return 0;
}
