#include <stdio.h>
#include <ctype.h>
#include "dbg.h"

// To build as a shared library:
//   cc -c libex29.c -o libex29.o
//   cc -shared -o libex29.so libex29.o

int print_a_message(const char *msg)
{
    printf("A STRING: %s\n", msg);
    return 0;
}

int uppercase(const char *msg)
{
    int i = 0;

    // \0 termination problems
    for (i = 0; msg[i] != '\0'; i++) {
        printf("%c", toupper((int)msg[i]));
    }

    printf("\n");

    return 0;
}

int lowercase(const char *msg)
{
    int i = 0;

    // \0 termination problems
    for (i = 0; msg[i] != '\0'; i++) {
        printf("%c", tolower((int)msg[i]));
    }

    printf("\n");

    return 0;
}

int fail_on_purpose(const char *msg)
{
    printf("FAIL ON PURPOSE MESSAGE: %s\n", msg);
    return 1;
}
