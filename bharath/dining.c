#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Mutexes to represent forks
pthread_mutex_t forks[NUM_PHILOSOPHERS];

// Function to simulate philosopher's thinking and eating
void* philosopher(void* arg) {
    int id = *(int*)arg;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", id);
        usleep(rand() % 1000);  // Simulate thinking time

        // Trying to pick up forks
        printf("Philosopher %d is hungry.\n", id);
        
        // Pick up left fork (mutex for forks[id])
        pthread_mutex_lock(&forks[id]);

        // Pick up right fork (mutex for forks[(id + 1) % NUM_PHILOSOPHERS])
        pthread_mutex_lock(&forks[(id + 1) % NUM_PHILOSOPHERS]);

        // Eating
        printf("Philosopher %d is eating.\n", id);
        usleep(rand() % 1000);  // Simulate eating time

        // Put down right fork
        pthread_mutex_unlock(&forks[(id + 1) % NUM_PHILOSOPHERS]);

        // Put down left fork
        pthread_mutex_unlock(&forks[id]);

        // Done eating, continue thinking
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize mutexes for each fork
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, (void*)&philosopher_ids[i]);
    }

    // Wait for philosopher threads to finish (although they never will in this case)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Clean up mutexes (never reached in this program due to infinite loop)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
