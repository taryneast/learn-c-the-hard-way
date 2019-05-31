#include <stdio.h>
#include <stdlib.h>

void print_array(int *my_array, int array_length) {
    int i = 0;
    for (i = 0; i < array_length; i++) {
        printf("%d: %d\n", i, my_array[i]);
    }
}

/* Quick and dirty reduce-equvalent... but only works for ints */
int reduce(int default_value, int *original_array, int array_length, int (*my_func)(int, int)) {
    int accumulator = default_value;
    int i = 0;

    for (i=0; i < array_length; i++) {
        accumulator = my_func(accumulator, original_array[i]);
    }

    return accumulator;
}

int sum(int sum_so_far, int num) {
    return sum_so_far + num;
}

int max(int max_so_far, int num) {
    if (num > max_so_far) {
        return num;
    }

    return max_so_far;
}

int min(int min_so_far, int num) {
    if (num < min_so_far) {
        return num;
    }

    return min_so_far;
}


int main(int argc, char *argv[]) {
    int my_array[] = {6, 2, 4, 1, 5, 3};
    int array_length = sizeof(my_array)/sizeof(int);
    int sum_value = 0;
    int max_value = 0;
    int min_value = 99;

    printf("Start with:\n");
    print_array(my_array, array_length);

    printf("Now trying sum\n");
    sum_value = reduce(sum_value, my_array, array_length, &sum);
    printf("Got sum of: %d\n", sum_value);

    printf("Now trying max\n");
    max_value = reduce(max_value, my_array, array_length, &max);
    printf("Got max of: %d\n", max_value);

    printf("Now trying min\n");
    min_value = reduce(min_value, my_array, array_length, &min);
    printf("Got min of: %d\n", min_value);

    return 0;
}
