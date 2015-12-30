#include <stdio.h>
#include "fib2.h"

int fib(int n)
{
    printf("fib() in fib2.c\n");
    if (n == 0 || n == 1) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}
