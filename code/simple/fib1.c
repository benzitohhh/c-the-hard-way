#include <stdio.h>
#include "fib1.h"

int fib(int n)
{
    printf("fib() in fib1.c\n");
    if (n == 0 || n == 1) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}
