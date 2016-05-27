#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    // See http://nuclear.mutantstargoat.com/articles/pointers_explained.pdf

    int a = 10;
    int *p = &a; // assign the address of a, to p (an integer pointer)
    printf("a contains the value %d\n", a);
    printf("p points to %p\n", p);
    printf("there lies the value %d\n", *p);

    printf("\n");

    char *cptr = (char*)2;
    printf("cptr before: %p ", cptr);
    cptr++;
    printf("and after: %p\n", cptr);

    int *iptr = (int*)2;
    printf("iptr before: %p ", iptr);
    iptr++;
    printf("and after: %p\n", iptr);

    printf("\n");

    char *s = "a string of chars";
    printf("s is a pointer, that holds address: %p\n", s);
    printf("s points to: '%s'\n", s);

    int w = strlen(s);
    printf("w = %d\n", w);
    for (int i = 0; i < w; i++) {
        printf("s[%d]: %c\n", i, s[i]);
    }
    printf("s[w]: %c\n", s[w]); // last character is the string terminator '\0', aka the null char
    printf("null char: %c\n", '\0');

    printf("\n");

    // Note that both "int *p" and "int* p" are valid.
    // Often C uses the former, while C++ uses the latter.
    // http://www.stroustrup.com/bs_faq2.html#whitespace

    // An array, and a pointer to an array, are almost interchangable
    // The only difference is that the compiler has some size data for the array.
    short *q;
    short arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    q = arr;
    printf("arr[2]: %d\n", arr[2]);
    printf("q[2]: %d\n", q[2]);
    printf("*(arr+2): %d\n", *(arr+2));
    printf("sizeof(arr): %d\n", (int)sizeof(arr));
    printf("sizeof(q): %d\n", (int)sizeof(q)); // how much space the pointer itself occupies

    int nelem = 3;
    int *arr2 = malloc(nelem * sizeof(int));
    // use arr2 here
    arr2[0] = 1;
    arr2[1] = 2;
    arr2[2] = 3;
    for (int i = 0; i < nelem; i++) {
        printf("arr2[%d]: %d\n", i, arr2[i]); // yes we can...
    }

    arr2[3] = 4; // can we do this? Maybe...
    printf("arr2[%d]: %d\n", 4, arr2[4]); // Maybe (it's dangerous)

    // int big = 20000000;
    // arr2[big] = 5; // can we do this? No - segfault
    // printf("arr2[big]: %d\n", arr2[big]);

    free(arr2);

    double (*foo)(double); // a function pointer called foo
    foo = sin; // assign sin (the address containing function sin) to foo
    printf("sine of 0 is: %f\n", foo(0.0));
    foo = cos;
    printf("cosine of 0 is %f\n", foo(0.0));

    return 0;
}
