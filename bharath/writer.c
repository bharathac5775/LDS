#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>    // For O_CREAT, O_RDWR
#include <sys/mman.h> // For shm_open, mmap
#include <unistd.h>   // For ftruncate
#include <string.h>

#define SHARED_MEM_NAME "/shared_mem_example"
#define SHARED_MEM_SIZE 1024

int main() {
    int shm_fd;
    char *shared_mem;

    // Step 1: Create and open shared memory
    shm_fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Step 2: Set the size of the shared memory
    if (ftruncate(shm_fd, SHARED_MEM_SIZE) == -1) {
        perror("ftruncate");
        exit(1);
    }

    // Step 3: Map the shared memory
    shared_mem = mmap(0, SHARED_MEM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_mem == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Step 4: Write the string to shared memory
    strcpy(shared_mem, "Hello There");
    printf("Writer: Wrote the string to shared memory: %s\n", shared_mem);

    // Step 5: Unmap and close shared memory
    if (munmap(shared_mem, SHARED_MEM_SIZE) == -1) {
        perror("munmap");
        exit(1);
    }
    close(shm_fd);

    return 0;
}