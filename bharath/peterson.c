#include <stdio.h>
#include <pthread.h>

// Global shared variable
int shared_var = 0;

// Peterson's algorithm variables
int flag[2] = {0, 0};  // flag[0] and flag[1] will indicate if thread 0 or 1 wants to enter critical section
int turn;               // turn variable to decide whose turn it is to enter critical section

// Function to increment shared_var by 100 (Thread 1)
void* thread_1(void* arg) {
    for (int i = 0; i < 5; i++) {  // Run for 5 iterations
        flag[0] = 1;  // Thread 1 wants to enter the critical section
        turn = 1;      // Give the other thread a chance to enter critical section
        
        // Wait until it's thread 1's turn and thread 2 isn't interested in the critical section
        while (flag[1] == 1 && turn == 1);
        
        // Critical section
        shared_var += 100;
        printf("Thread 1: Incremented shared_var by 100. New value: %d\n", shared_var);
        
        // Exit critical section
        flag[0] = 0;
    }
    return NULL;
}

// Function to decrement shared_var by 75 (Thread 2)
void* thread_2(void* arg) {
    for (int i = 0; i < 5; i++) {  // Run for 5 iterations
        flag[1] = 1;  // Thread 2 wants to enter the critical section
        turn = 0;      // Give the other thread a chance to enter critical section
        
        // Wait until it's thread 2's turn and thread 1 isn't interested in the critical section
        while (flag[0] == 1 && turn == 0);
        
        // Critical section
        shared_var -= 75;
        printf("Thread 2: Decremented shared_var by 75. New value: %d\n", shared_var);
        
        // Exit critical section
        flag[1] = 0;
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Create threads
    pthread_create(&t1, NULL, thread_1, NULL);
    pthread_create(&t2, NULL, thread_2, NULL);
    
    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    // Final result
    printf("Final value of shared_var: %d\n", shared_var);
    
    return 0;
}
