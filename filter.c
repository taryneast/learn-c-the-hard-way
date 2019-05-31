#include <stdio.h>
#include <stdlib.h>

void print_array(int *my_array, int array_length) {
    int i = 0;
    for (i = 0; i < array_length; i++) {
        printf("%d: %d\n", i, my_array[i]);
    }
}

/* Quick and dirty filter-equvalent... but only works for ints */
int *filter(int *original_array, int array_length, int (*my_func)(int)) {
    int *tmp_array = malloc(sizeof(int) * (array_length + 1));
    int i = 0;
    int j = 1;

    for (i=0; i < array_length; i++) {
        if (my_func(original_array[i])) {
            tmp_array[j] = original_array[i];
            j++;
        }
    }

    // Store number of matching items
    tmp_array[0] = j-1;

    return tmp_array;
}

int odd(int num) {
    return (1 == num % 2);
}

int even(int num) {
    return (0 == num % 2);
}

int div_by_5(int num) {
    return (0 == num % 5);
}

int main(int argc, char *argv[]) {
    int my_array[] = {7, 15, 6, 1, 9, 42, 22, 10, 5, 3};
    int array_length = sizeof(my_array)/sizeof(int);
    int new_array_length = 0;
    int *new_array;

    printf("Start with:\n");
    print_array(my_array, array_length);

    printf("Now finding odds\n");
    new_array = filter(my_array, array_length, &odd);
    new_array_length = new_array[0];
    printf("new array should have %d items\n", new_array_length);
    print_array(new_array + 1, new_array_length);

    printf("Now finding evens\n");
    new_array = filter(my_array, array_length, &even);
    new_array_length = new_array[0];
    printf("new array should have %d items\n", new_array_length);
    print_array(new_array + 1, new_array_length);

    printf("Now finding multiples of 5\n");
    new_array = filter(my_array, array_length, &div_by_5);
    new_array_length = new_array[0];
    printf("new array should have %d items\n", new_array_length);
    print_array(new_array + 1, new_array_length);

    return 0;
}
