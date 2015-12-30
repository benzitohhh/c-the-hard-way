// A. Compile fib objects
//   cc -Wall -g   -c -o fib1.o fib1.c
//   cc -Wall -g   -c -o fib2.o fib2.c

// B. Compile and link main
//   cc -Wall -g    main.c fib1.o   -o main            # OK
//   cc -Wall -g    main.c fib2.o   -o main            # OK
//   cc -Wall -g    main.c fib1.o fib2.o   -o main     # This will barf

#include <stdio.h>

int fib(int n); // Linker will find definition of this function.
// But.... if there are multiple definitions (i.e. B line 3), linker will barf

int main(int argc, char *argv[])
{
    int n = 5;
    int res = fib(n);
    printf("res(%d): %d\n", n, res);
    return 0;
}
