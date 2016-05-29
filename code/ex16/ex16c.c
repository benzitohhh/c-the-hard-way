#include <stdlib.h>

struct Person {
    int age;
    int height;
};

int main(int argc, char *argv[])
{
    struct Person *p1 = malloc(8); // allocate memory in heap, get a pointer to it
    p1->age = 23; // use the pointer to get a particular address in the heap memory, and write to it

    struct Person p2; // allocate memory on stack
    p2.age = 28; // writes to the stack
    
    return 0;
}
