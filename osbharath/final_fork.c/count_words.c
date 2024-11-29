// count_words.c
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

    int words = 0;
    char ch, prev_ch = ' ';
    while ((ch = fgetc(file)) != EOF) {
        if (!isspace(ch) && isspace(prev_ch)) {
            words++;
        }
        prev_ch = ch;
    }

    fclose(file);
    printf("Total number of words: %d\n", words);
    return 0;
}
