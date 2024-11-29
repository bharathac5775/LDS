#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();  // Create a new process

    if (pid < 0) {
        // fork failed
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // This is the child process
        printf("I’m the child. My PID is %d and my parent’s PID is %d\n", getpid(), getppid());
    } else {
        // This is the parent process
        printf("I’m the parent. My PID is %d and my child’s PID is %d\n", getpid(), pid);
    }

    return 0;
}

