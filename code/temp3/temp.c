#include <stdio.h>
#include <stdlib.h>

// #define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

// log_err("hello", "there");

#define check_mem(A) check((A), "Out of memory.")



int main(int argc, char *argv[])
{
    //char *s = "hello there";

    char *s = NULL;  // 0


    printf("s: %p\n", s);
    printf("*s: %c\n", *s);
    return 0;
}
