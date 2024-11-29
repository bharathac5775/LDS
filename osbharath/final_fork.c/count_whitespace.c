// count_whitespace.c
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    int whitespaces = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch)) {
            whitespaces++;
        }
    }

    fclose(file);
    printf("Total whitespace characters: %d\n", whitespaces);
    return 0;
}
