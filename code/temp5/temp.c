#include <stdio.h>
#include "lib.h"

void some_other_func()
{
    printf("some_other_func()\n");
}

void and_another_func(int a)
{
    printf("and_another_func(%d)\n", a);
}


int main(int argc, char *argv[])
{
    my_func();
    my_other_func(3);
    some_other_func();
    and_another_func(5);

    // No compiler error or warning (works okish...)
    my_func(3, 4, 5);
    my_other_func(); // looks on stack, gets a weird value...

    // Compiler warning (no error)
    //some_other_func(3, 4, 5);

    // // Compiler error
    //and_another_func(5, 6);
    //and_another_func();

    // So seems like...
    // for library functions... compiler does not check args
    // for in-file functions (at least one arg)... compiler checks
    // for in-file functions (no args)... compiler checks, but will allow many args to be passed

    // Maybe this is to facilitate varargs stuff???

    return 0;
}
