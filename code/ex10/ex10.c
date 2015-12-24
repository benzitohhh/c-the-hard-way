#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    // go theough each string in argv
    // why am I skipping argv[0]? Because it's the arg count.
    for (i = 1; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    // So... argv is an array of char arrays (i.e. an array of strings)
    //       *argv is the memory location where argv starts???



    // Here's a string
    char *myString = "yay";
    printf("myString: %s\n", myString); // so myString is an "array of chars"
    printf("*myString: %d\n", *myString); // and *mySting is a pointer to the memory location where myString array starts

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };
    int num_states = 4;

    for (i = 0; i < num_states; i++) {
        printf("state %d: %s\n", i, states[i]);
    }


    return 0;
}
