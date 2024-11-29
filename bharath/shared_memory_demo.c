#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Shared memory size

int main() {
    key_t key;
    int shmid;
    char *data;
    int mode;

    // Step 1: Create a unique key for shared memory
    if ((key = ftok("shmfile", 65)) == -1) {
        perror("ftok");
        exit(1);
    }

    // Step 2: Create a shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    // Step 3: Attach the shared memory segment to the process
    if ((data = (char *)shmat(shmid, (void *)0, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Choose an option:\n");
    printf("1. Write to shared memory\n");
    printf("2. Read from shared memory\n");
    scanf("%d", &mode);
    getchar(); // Clear newline character from input buffer

    if (mode == 1) {
        // Step 4a: Write to the shared memory
        printf("Enter some data to write to shared memory: ");
        fgets(data, SHM_SIZE, stdin);
        data[strcspn(data, "\n")] = '\0'; // Remove newline character
        printf("Data written to shared memory: %s\n", data);
    } else if (mode == 2) {
        // Step 4b: Read from the shared memory
        printf("Data read from shared memory: %s\n", data);
    } else {
        printf("Invalid option.\n");
    }

    // Step 5: Detach the shared memory segment
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Step 6: Mark the shared memory segment for deletion
    if (mode == 2) {
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
        printf("Shared memory segment deleted.\n");
    }

    return 0;
}
