#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight) {
    struct Person *who = malloc(sizeof(struct Person));
    assert(who !=NULL);

    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void Person_destroy(struct Person *who) {
    assert(who !=NULL);

    free(who->name);
    free(who);
}

void Person_print(struct Person *who) {
    printf("Name: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\tHeight: %d\n", who->height);
    printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[]) {
    // make two people structures
    struct Person *joe = Person_create("Joe Alex", 32, 64, 140);
    struct Person *jane = Person_create("Jane Black", 43, 54, 170);

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", joe);
    Person_print(joe);
    printf("Jane is at memory location %p:\n", jane);
    Person_print(jane);

    // age everyone by 20 years and print them out again
    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    Person_print(joe);

    jane->age += 20;
    jane->height -= 3;
    jane->weight -= 40;
    Person_print(jane);

    // destroy them both
    Person_destroy(joe);
    Person_destroy(jane);

    return 0;
}
