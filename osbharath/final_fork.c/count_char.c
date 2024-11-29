// count_char.c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "This is a sample string";
    char target = 's';
    int count = 0;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == target) {
            count++;
        }
    }

    printf("The character '%c' occurs %d times.\n", target, count);
    return 0;
}
