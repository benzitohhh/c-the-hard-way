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

struct Person *Person_create(char *name, int age, int height, int weight)
{
    struct Person *who = malloc(sizeof(struct Person)); // create on the heap
    assert(who != NULL);

    who->name = strdup(name); // make sure that this instance has its own private copy (so that noone else can change the chars)
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void Person_destroy(struct Person *who)
{
    assert(who != NULL);

    free(who->name);
    free(who);
}

void Person_print(struct Person *who)
{
    printf("Name: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\tHeight: %d\n", who->height);
    printf("\tWeight: %d\n", who->weight);
}

struct Person Person_create_stack(char *name, int age, int height, int weight)
{
    struct Person who; // create on stack

    who.name = strdup(name); // create private copy (so that noone else can change the chars)
    who.age = age;
    who.height = height;
    who.weight = weight;

    return who;
}

void Person_print_stack(struct Person who)
{
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\tHeight: %d\n", who.height);
    printf("\tWeight: %d\n", who.weight);
}

void heap_example()
{
    struct Person *joe = Person_create("Joe Alex Heap", 32, 64, 140);
    struct Person *frank = Person_create("Frank Blank Heap", 20, 72, 180);

    printf("Joe is at memory location %p\n", joe);
    Person_print(joe);

    printf("Frank is at memory location %p\n", joe);
    Person_print(joe);

    // make everyone age 20 years and print them again
    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    Person_print(joe);

    frank->age += 20;
    frank->weight += 20;
    Person_print(frank);

    // destroy them both so we clean up
    Person_destroy(joe);
    Person_destroy(frank);
}

void stack_example()
{
    struct Person joe_stack = Person_create_stack("Joe Stack Alex", 32, 64, 140);
    Person_print_stack(joe_stack);

    struct Person frank_stack = Person_create_stack("Frank stack", 20, 32, 77);
    Person_print_stack(frank_stack);
   
    joe_stack.name = strdup("Some new name");
    Person_print_stack(joe_stack);
    Person_print_stack(frank_stack);    
}

int main(int argc, char *argv[])
{
    printf("\n");
    heap_example();

    printf("\n");    
    stack_example();
    return 0;
}
