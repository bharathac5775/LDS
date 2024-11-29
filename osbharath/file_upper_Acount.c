#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>

void convert_to_uppercase(const char *filename) {
    FILE *file = fopen(filename, "r+"); // Open the file in read+write mode
    if (file == NULL) {
        perror("Failed to open file for uppercase conversion");
        exit(1);
    }

    char ch;
    long pos;
    while ((ch = fgetc(file)) != EOF) {
        if(islower(ch)){
            pos=ftell(file);
            fseek(file,pos-1,SEEK_SET);
            fputc(toupper(ch),file);
            fseek(file,pos,SEEK_SET);
        }
    }

    fclose(file);
    printf("Child 1: Converted all lowercase characters to uppercase.\n");
}

void count_a_characters(const char *filename) {
    FILE *file = fopen(filename, "r"); // Open the file in read mode
    if (file == NULL) {
        perror("Failed to open file for character counting");
        exit(1);
    }

    int a_count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == 'a' || ch == 'A') {  // Count both lowercase and uppercase 'a'
            a_count++;
        }
    }

    fclose(file);
    printf("Child 2: Total occurrences of character 'a' or 'A' = %d\n", a_count);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    pid_t pid1, pid2;

    // Create the first child process for uppercase conversion
    pid1 = fork();
    if (pid1 < 0) {
        perror("Failed to fork first child");
        return 1;
    } else if (pid1 == 0) {
        // First child process
        convert_to_uppercase(argv[1]);
        exit(0);
    }

    // Create the second child process for counting 'a' characters
    pid2 = fork();
    if (pid2 < 0) {
        perror("Failed to fork second child");
        return 1;
    } else if (pid2 == 0) {
        // Second child process
        count_a_characters(argv[1]);
        exit(0);
    }

    // Parent process waits for both children to complete
    wait(NULL); // Wait for the first child
    wait(NULL); // Wait for the second child

    printf("Parent: Both child processes completed.\n");

    return 0;
}
