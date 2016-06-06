#include <stdio.h>
#include <stdlib.h>

// #define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

// log_err("hello", "there");

#define check_mem(A) check((A), "Out of memory.")



int main(int argc, char *argv[])
{
    char *s = "hello there";

    char a[] = "and hello again";

    char *p = a;

    char *q;
    q = a;

    char *z;
    z = (char *)&a;
    //char *s = NULL;  // 0

    long ia = (long)&a;  // &a and a evaluate to the same memory address....
    long ib = (long)a;

    printf("s:  %p\n", s);
    printf("*s: %c\n", *s);
    printf("*s: %s\n", s);
    printf("a:  %s\n", a);
    //printf("a:  %s\n", a[0]); segfault, becuase looks address of (int)('a')
    printf("p:  %s\n", p);
    printf("q:  %s\n", q);
    printf("z:  %s\n", z);

    printf("a:  %p\n", a); // a evaluates to the address of a[0]
    printf("q:  %p\n", q); // q also evaluates to the address of a[0]

    printf("ia:  %s\n", (char *)ia);
    printf("ib:  %s\n", (char *)ib);

    return 0;
}
