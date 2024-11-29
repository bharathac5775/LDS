#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <ctype.h>

// Define the shared memory name
#define SHM_NAME "/my_shared_mem"

// Shared memory structure
typedef struct {
    char str[100];
    pthread_mutex_t mutex;
} SharedData;

// Function to convert case
void convert_case(char *str) {
    for (int i = 0; str[i]; i++) {
        if (islower(str[i])) {
            str[i] = toupper(str[i]);
        } else if (isupper(str[i])) {
            str[i] = tolower(str[i]);
        }
    }
}

// First thread: Writes the string to shared memory
void* write_thread(void *arg) {
    SharedData *sharedData = (SharedData *)arg;

    pthread_mutex_lock(&sharedData->mutex);

    // Write the string "Hello There" to shared memory
    strcpy(sharedData->str, "Hello There");
    printf("First Thread: Written string to shared memory: %s\n", sharedData->str);

    pthread_mutex_unlock(&sharedData->mutex);

    return NULL;
}

// Second thread: Reads, converts case, and writes back to shared memory
void* read_and_convert_thread(void *arg) {
    SharedData *sharedData = (SharedData *)arg;

    // Wait until the first thread writes the string
    pthread_mutex_lock(&sharedData->mutex);

    // Read the string, convert its case, and write back to shared memory
    printf("Second Thread: Read string from shared memory: %s\n", sharedData->str);
    convert_case(sharedData->str);
    printf("Second Thread: Converted string to: %s\n", sharedData->str);

    pthread_mutex_unlock(&sharedData->mutex);

    return NULL;
}

// First thread: Reads the string after it was converted by the second thread
void* final_read_thread(void *arg) {
    SharedData *sharedData = (SharedData *)arg;

    // Wait until the second thread has finished modifying the string
    pthread_mutex_lock(&sharedData->mutex);

    // Read the string after conversion and print it
    printf("First Thread: Final read after conversion: %s\n", sharedData->str);

    pthread_mutex_unlock(&sharedData->mutex);

    return NULL;
}

int main() {
    // Open shared memory object
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Set the size of the shared memory object
    if (ftruncate(shm_fd, sizeof(SharedData)) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Map the shared memory object
    SharedData *sharedData = mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (sharedData == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Initialize the mutex in the shared memory
    if (pthread_mutex_init(&sharedData->mutex, NULL) != 0) {
        perror("Mutex init failed");
        exit(EXIT_FAILURE);
    }

    // Create the threads
    pthread_t thread1, thread2, thread3;

    // First thread writes the string
    pthread_create(&thread1, NULL, write_thread, sharedData);

    // Second thread reads, converts, and writes back to shared memory
    pthread_create(&thread2, NULL, read_and_convert_thread, sharedData);

    // Third thread reads the final string after conversion
    pthread_create(&thread3, NULL, final_read_thread, sharedData);

    // Wait for all threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // Clean up: unmap and close shared memory
    if (munmap(sharedData, sizeof(SharedData)) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    if (shm_unlink(SHM_NAME) == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }

    // Destroy mutex
    if (pthread_mutex_destroy(&sharedData->mutex) != 0) {
        perror("Mutex destroy failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
