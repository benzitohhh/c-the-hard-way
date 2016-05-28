#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("\n");
    printf("&argv, argv                %p %p  # outer pointer: address, value\n", &argv, argv);  // outer pointer: address

    for (int i=0; i < argc; i++) {
        printf("(argv + %d), *(argv + %d):   %p %p  # inner pointer %d: address, value\n", i, i, (argv + i), *(argv + i), i);
    }

    // For each word, for each char, print address, value
    for (int i=0; i < argc; i++) {
        int length = strlen(argv[i]);
        int size = sizeof(argv[i]);
        printf("%d length: %d\n", i, length);
        printf("%d size: %d\n", i, size);

        for (int j=0; j < length + 1; j++) {
            printf("&(arg[%d][%d]), arg[%d][%d]:   %p  %c    # value %d: address, value\n", i, j, i, j, &(argv[i][j]), argv[i][j], j);
        }

    }

    printf("\n");

    /*
    int distance = 100;
    float power = 2.345f;
    double super_power = 56789.4532;
    char initial = 'A';
    char first_name[] = "Zed";
    char last_name[] = "Shaw";

    printf("You are %d miles away.\n", distance);
    printf("You have %f levels of power.\n", power);
    printf("You have %f awesome super powers.\n", super_power);
    printf("I have an initial %c.\n", initial);
    printf("I have a first name %s.\n", first_name);
    printf("I have a last name %s.\n", last_name);
    printf("My whole name is %s %c %s.\n",
           first_name, initial, last_name);
    */

    return 0;
}
