#include <stdio.h>

void my_if(int i) {
    if (i) {
        printf("if(%d): true\n", i);
    } else {
        printf("if(%d): false\n", i);
    }
}

int main(int argc, char *argv[])
{
    // my_if(0);
    // my_if(1);
    // my_if(-1);
    int i = 1;
    int j = 2;

    if (i && j % 2) {
        printf("if(%d && %d %% 2): true\n", i, j);
    } else {
        printf("if(%d && %d %% 2): false\n", i, j);
    }

    return 0;
}
