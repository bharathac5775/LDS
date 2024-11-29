#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_READERS 2
#define FILENAME "shared_file.txt"

// Mutex for protecting file access
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Condition variable to signal when the writer has updated the file
pthread_cond_t cond_writer = PTHREAD_COND_INITIALIZER;
int writer_done = 0;  // Flag to indicate if the writer has finished updating the shared variable

// Function to read the value from the file
int read_from_file() {
    int value = 0;
    FILE *file = fopen(FILENAME, "r");
    if (file != NULL) {
        fscanf(file, "%d", &value);  // Read the integer value from the file
        fclose(file);
    } else {
        perror("Error opening file for reading");
    }
    return value;
}

// Function to write the updated value to the file
void write_to_file(int value) {
    FILE *file = fopen(FILENAME, "w");
    if (file != NULL) {
        fprintf(file, "%d", value);  // Write the value to the file
        fclose(file);
    } else {
        perror("Error opening file for writing");
    }
}

// Reader thread function
void* reader(void* arg) {
    int reader_id = *((int*)arg); // Get the reader ID

    // Wait until the writer has finished updating the file
    pthread_mutex_lock(&mutex);
    while (writer_done == 0) {
        pthread_cond_wait(&cond_writer, &mutex);  // Wait for the writer to complete
    }

    // Reader reads the value from the file
    int value = read_from_file();
    printf("Reader %d: Read value = %d\n", reader_id, value);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Writer thread function
void* writer(void* arg) {
    // Writer increments the value in the file by 35
    pthread_mutex_lock(&mutex);

    // Read the current value from the file
    int value = read_from_file();
    printf("Writer: Read value = %d\n", value);

    // Increment the value by 35
    value += 35;
    printf("Writer: Incremented value by 35. New value = %d\n", value);

    // Write the updated value back to the file
    write_to_file(value);

    // Notify all readers that the writer has finished its work
    writer_done = 1;
    pthread_cond_broadcast(&cond_writer);  // Signal all readers

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writer_thread;
    int reader_ids[NUM_READERS];

    // Initialize the file with the initial value 25
    write_to_file(25);

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
