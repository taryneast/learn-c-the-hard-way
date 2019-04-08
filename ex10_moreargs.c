#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("ERROR: you need to add at least one argument\n");
        // this is how you abort a program
        return 1;
    }

    for (int n = 1; n < argc; n++) {
        printf("arg: %d of %d - %s\n", n, argc - 1, argv[n]);

        char letter = '\0';

        for (int i = 0; (letter = argv[n][i]) != '\0'; i++) {

            switch (tolower(letter)) {
                case 'a':
                    printf("%d: 'A'\n", i);
                    break;

                case 'e':
                    printf("%d: 'E'\n", i);
                    break;

                case 'i':
                    printf("%d: 'I'\n", i);
                    break;

                case 'o':
                    printf("%d: 'O'\n", i);
                    break;

                case 'u':
                    printf("%d: 'U'\n", i);
                    break;

                case 'y':
                    if (i > 2) {
                        // it's only sometimes Y
                        printf("%d: 'Y'\n", i);
                        break;
                    }
                    // else fall through to default case

                default:
                    printf("%d: %c is not a vowel\n", i, letter);
            }
        }
    }

    return 0;
}
