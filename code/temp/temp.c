#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int a[] = {5, 6, 7};

    int len = sizeof(a) / sizeof(int);

    printf("\n\n%p, %p\n", a, &a);
    for (int i = 0; i < len; i++) {
        printf("a[%d]: %d, %p\n", i, a[i], &(a[i]));
    }

    return 0;
}
