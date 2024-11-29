#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_READERS 2

// Global shared variable
int shared_var = 0;

// Mutex for protecting shared variable
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Condition variable to signal when the writer has updated the shared variable
pthread_cond_t cond_writer = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_reader = PTHREAD_COND_INITIALIZER;

int writer_done = 0;  // Flag to indicate if the writer has finished updating the shared variable

// Reader thread function
void* reader(void* arg) {
    int reader_id = *((int*)arg); // Get the reader ID

    // Wait until the writer has finished updating the shared variable
    pthread_mutex_lock(&mutex);
    while (writer_done == 0) {
        pthread_cond_wait(&cond_writer, &mutex);  // Wait for the writer to complete
    }
    
    // Reader reads the shared variable
    printf("Reader %d: Read shared_var = %d\n", reader_id, shared_var);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Writer thread function
void* writer(void* arg) {
    // Writer increments the shared variable by 35
    pthread_mutex_lock(&mutex);
    shared_var += 35;
    printf("Writer: Incremented shared_var by 35. New value = %d\n", shared_var);

    // Notify all readers that the writer has finished its work
    writer_done = 1;
    pthread_cond_broadcast(&cond_writer);  // Signal all readers

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writer_thread;
    int reader_ids[NUM_READERS];

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;  // Assign reader ID
        pthread_create(&readers[i], NULL, reader, (void*)&reader_ids[i]);
    }

    // Create writer thread
    pthread_create(&writer_thread, NULL, writer, NULL);

    // Wait for the writer to finish
    pthread_join(writer_thread, NULL);

    // Wait for all reader threads to finish
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Destroy mutex and condition variable
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_writer);

    return 0;
}
