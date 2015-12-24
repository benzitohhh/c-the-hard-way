#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    printf("argc: %d\n", argc);
    if(argc == 1) {
        printf("You only have one argument. You suck,\n");
    } else if(argc > 1 && argc < 4) {
        printf("Here's your arguments:\n");

        for (i = 0; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    } else {
        printf("You have too many arguments. You such.\n");
    }

    return 0;
}
