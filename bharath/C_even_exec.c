// even_series.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of terms>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); // Convert the command-line argument to an integer
    if (n < 1) {
        fprintf(stderr, "The number of terms must be a positive integer.\n");
        return 1;
    }

    printf("Child process: Generating even series up to %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", 2 * i); // Generates 0, 2, 4, 6, ...
    }
    printf("\n");

    return 0;
}
