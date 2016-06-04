#include "ex22.h"
#include "dbg.h"

// To compile: make clean; make -k all; ./ex22_main;

const char *MY_NAME = "Zed A. Shaw";

int main(int argc, char *argv[])
{
    // // //STATIC
    // log_info("My name: %s, age: %d", MY_NAME, get_age());
    // set_age(100);
    // log_info("My age is now: %d", get_age());
    // //log_info("THE_AGE: %d", THE_AGE); // compile error

    // // //EXTERN
    // log_info("THE_SIZE is: %d", THE_SIZE);
    // print_size();
    // THE_SIZE = 9;
    // log_info("THE_SIZE is now: %d", THE_SIZE);
    // print_size();
    // int THE_SIZE = 123; // local variable (does not affect the extern)
    // log_info("THE_SIZE is now: %d", THE_SIZE);
    // print_size();

    // //static within function
    log_info("Ratio at first: %f", update_ratio(2.0));
    // log_info("Ratio again: %f", update_ratio(10.0));
    // log_info("Ratio once more: %f", update_ratio(300.0));

    return 0;
}
