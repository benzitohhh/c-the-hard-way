#include "ex22.h"
#include "dbg.h"

// Compile ex22.c to an object file:
//    gcc -Wall -g -DNDEBUG   -c -o ex22.o ex22.c

// Compile and link ex22_main.c (using ex22.o)
//    gcc -Wall -g -DNEDBUG   ex22_main.c ex22.o    -o ex22_main

const char *MY_NAME = "Zed A. Shaw";

void scope_demo(int count)
{
    log_info("count is: %d", count);

    if(count > 10) {
        int count = 100; // BAD! BUGS!

        log_info("count in this scope is %d", count);
    }

    log_info("count is at exit: %d", count);

    count = 3000;

    log_info("count after assign: %d", count);
}

int fib(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}

int main(int argc, char *argv[])
{
    // test out THE_AGE accessors
    log_info("My name: %s, age: %d", MY_NAME, get_age());

    set_age(100);

    log_info("My age is now: %d", get_age());

    // test out THE_SIZE extern
    log_info("THE SIZE is: %d", THE_SIZE);
    print_size();

    THE_SIZE = 9;

    log_info("THE SIZE is now: %d", THE_SIZE);
    print_size();

    // test the ratio function static
    log_info("Ratio at first: %f", update_ratio(2.0));
    log_info("Ratio again: %f", update_ratio(10.0));
    log_info("Ratio once more: %f", update_ratio(300.0));

    // test the scope demo
    int count = 4;
    scope_demo(count);
    scope_demo(count * 20);

    log_info("count after calling scope_demo: %d", count);

    log_info("Calling recursive function...");
    int fib_res = fib(10);
    log_info("fib_res: %d", fib_res);
    return 0;
}
