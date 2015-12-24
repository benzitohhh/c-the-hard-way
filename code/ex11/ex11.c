#include <stdio.h>

int main(int argc, char *argv[])
{
    // Go through each string in argv

    int i = 0;
    while (i < argc) {
        printf("arg %d: %s\n", i, argv[i]);
        i++;
    }

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    /* int num_states = 4; */
    i = 3;
    while (i >= 0) {
        printf("states %d: %s\n", i, states[i]);
        i--;
    }
    return 0;
}
