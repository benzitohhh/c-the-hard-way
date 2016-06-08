#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("allocate memory\n");
    int *p = malloc(4 * sizeof(int));

    p[0] = 21;
    p[1] = 22;
    p[2] = 23;
    p[3] = 24;

    int i;
    for (i = 0; i < 4; i++) {
        printf("p[%d]: %d\n", i, p[i]);
    }

    printf("reallocate memory\n");
    p = realloc(p, 2 * sizeof(int));

    for (i = 0; i < 4; i++) {
        printf("p[%d]: %d\n", i, p[i]);
    }

    printf("free memory\n");
    free(p);

    for (i = 0; i < 4; i++) {
        printf("p[%d]: %d\n", i, p[i]);
    }


    return 0;
}
