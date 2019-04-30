#include <stdio.h>
#include <ctype.h>

void print_letters(char arg[]) {
    int i = 0;
    char ch = ' ';

    for (i=0; (ch = arg[i]) != '\0'; i++) {
        if (isalpha((int)ch) || isblank((int)ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    int i = 0;

    for (i=0; i < argc; i++) {
        print_letters(argv[i]);
    }

    return 0;
}
