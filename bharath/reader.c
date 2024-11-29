#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>    // For O_RDONLY
#include <sys/mman.h> // For shm_open, mmap
#include <unistd.h>   // For shm_unlink
#include <ctype.h>    // For toupper

#define SHARED_MEM_NAME "/shared_mem_example"
#define SHARED_MEM_SIZE 1024

void to_uppercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    int shm_fd;
    char *shared_mem;

    // Step 1: Open shared memory
    shm_fd = shm_open(SHARED_MEM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Step 2: Map the shared memory
    shared_mem = mmap(0, SHARED_MEM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shared_mem == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Step 3: Read the string and convert it to uppercase
    char buffer[SHARED_MEM_SIZE];
    strncpy(buffer, shared_mem, SHARED_MEM_SIZE - 1);
    buffer[SHARED_MEM_SIZE - 1] = '\0'; // Ensure null termination
    printf("Reader: Read the string from shared memory: %s\n", buffer);

    to_uppercase(buffer);
    printf("Reader: String in uppercase: %s\n", buffer);

    // Step 4: Unmap and close shared memory
    if (munmap(shared_mem, SHARED_MEM_SIZE) == -1) {
        perror("munmap");
        exit(1);
    }
    close(shm_fd);

    // Step 5: Remove the shared memory object
    if (shm_unlink(SHARED_MEM_NAME) == -1) {
        perror("shm_unlink");
        exit(1);
    }
    printf("Reader: Shared memory segment removed.\n");

    return 0;
}
