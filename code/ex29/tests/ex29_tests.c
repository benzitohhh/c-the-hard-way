#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>

typedef int (*lib_function)(const char *data);

int check_func(void *lib, char *lib_file, char *func_to_run, char *data)
{
    int rc = 0;
    
    lib_function func = dlsym(lib, func_to_run);
    check(func != NULL, "Did not find %s function in the libarary %s: %s", func_to_run, lib_file, dlerror());

    rc = func(data);
    check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc, data);    

    return 0;
    
 error:
    return 1;
}

int main()
{
    int rc = 0;
    // check(argc == 4, "USAGE: ex29 libex29.so function data");

    // char *lib_file = argv[1];
    // char *func_to_run = argv[2];
    // char *data = argv[3];

    char *lib_file = "build/libex29.so";
    
    void *lib = dlopen(lib_file, RTLD_NOW);
    check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());

    check_func(lib, lib_file, "uppercase", "aYo");
    check_func(lib, lib_file, "lowercase", "aYo");
    check_func(lib, lib_file, "print_a_message", "aYo");

    rc = dlclose(lib);
    check(rc == 0, "Failed to close %s", lib_file);

    return 0;

 error:
    return 1;
}
