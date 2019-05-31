#include <stdio.h>
#include <stdlib.h>

void print_array(int *my_array) {
    int array_length = sizeof(*my_array);
    int i = 0;
    for (i = 0; i < array_length - 1; i++) {
        printf("%d: %d\n", i, my_array[i]);
    }
}

int *map(int *original_array, int (*my_func)(int)) {
    int array_length = sizeof(*original_array);
    int *new_array = malloc(sizeof(int) * array_length);
    int i = 0;


    for (i=0; i < array_length - 1; i++) {
        new_array[i] = my_func(original_array[i]);
    }

    return new_array;
}

int increment(int num) {
    return num + 1;
}

int double_me(int num) {
    return num * 2;
}

int main(int argc, char *argv[]) {
    int my_array[] = {1, 2, 3};
    int *new_array;

    printf("Start with:\n");
    print_array(my_array);

    printf("Now trying increment\n");
    new_array = map(my_array, &increment);
    print_array(new_array);

    printf("Now trying doubling\n");
    new_array = map(my_array, &double_me);
    print_array(new_array);

    return 0;
}
