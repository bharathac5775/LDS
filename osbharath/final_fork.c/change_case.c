// change_case.c
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char str[] = "Hello World!";
    printf("Original string: %s\n", str);

    for (int i = 0; i < strlen(str); i++) {
        if (islower(str[i])) {
            str[i] = toupper(str[i]);
        } else if (isupper(str[i])) {
            str[i] = tolower(str[i]);
        }
    }

    printf("String after case change: %s\n", str);
    return 0;
}
