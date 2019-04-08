#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("ERROR: you need to add at least one argument\n");
        // this is how you abort a program
        return 1;
    }

    int n = 1;
    int i = 0;
    for (n = 1; n < argc; n++) {
        printf("arg: %d of %d - %s\n", n, argc - 1, argv[n]);

        for (i = 0; argv[n][i] != '\0'; i++) {
            char letter = argv[n][i];

            switch (letter) {
                case 'a':
                case 'A':
                    printf("%d: 'A'\n", i);
                    break;

                case 'e':
                case 'E':
                    printf("%d: 'E'\n", i);
                    break;

                case 'i':
                case 'I':
                    printf("%d: 'I'\n", i);
                    break;

                case 'o':
                case 'O':
                    printf("%d: 'O'\n", i);
                    break;

                case 'u':
                case 'U':
                    printf("%d: 'U'\n", i);
                    break;

                case 'y':
                case 'Y':
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
