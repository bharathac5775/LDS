#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/shm_sequence"  // Name for the shared memory object
#define ARRAY_SIZE 5

// Shared structure to hold the sequence and the sum
typedef struct {
    int sequence[ARRAY_SIZE];  // Array to store the sequence of numbers
    int sum;                   // Sum of the sequence
    pthread_mutex_t mutex;     // Mutex for synchronization
} SharedData;

// Function for the first thread (writing numbers to shared memory)
void* write_sequence(void* arg) {
    SharedData* data = (SharedData*)arg;

    pthread_mutex_lock(&data->mutex); // Lock before writing

    // Writing a sequence of numbers to shared memory
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data->sequence[i] = i + 1;  // Simple sequence: 1, 2, 3, 4, 5
        printf("Writer Thread: Writing %d to shared memory\n", data->sequence[i]);
    }

    pthread_mutex_unlock(&data->mutex); // Unlock after writing

    return NULL;
}

// Function for the second thread (reading numbers from shared memory and calculating the sum)
void* calculate_sum(void* arg) {
    SharedData* data = (SharedData*)arg;
    int sum = 0;

    pthread_mutex_lock(&data->mutex); // Lock before reading

    // Calculate the sum of the sequence
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += data->sequence[i];
    }
    data->sum = sum;

    pthread_mutex_unlock(&data->mutex); // Unlock after reading

    printf("Reader Thread: Calculated sum = %d\n", data->sum);

    return NULL;
}

int main() {
    // Open shared memory region
    SharedData* data = (SharedData*)mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE,
                                         MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (data == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    // Initialize mutex
    if (pthread_mutex_init(&data->mutex, NULL) != 0) {
        perror("Mutex initialization failed");
        return 1;
    }

    // Create threads
    pthread_t writer_thread, reader_thread;
    if (pthread_create(&writer_thread, NULL, write_sequence, (void*)data) != 0) {
        perror("Failed to create writer thread");
        return 1;
    }
    if (pthread_create(&reader_thread, NULL, calculate_sum, (void*)data) != 0) {
        perror("Failed to create reader thread");
        return 1;
    }

    // Wait for threads to finish
    pthread_join(writer_thread, NULL);
    pthread_join(reader_thread, NULL);

    // Clean up
    pthread_mutex_destroy(&data->mutex);

    // Unmap shared memory
    if (munmap(data, sizeof(SharedData)) == -1) {
        perror("munmap failed");
        return 1;
    }

    return 0;
}
