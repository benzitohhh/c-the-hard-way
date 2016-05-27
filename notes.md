TODO:
install valgrind (see chapter 4)


To compile a file
*****************
gcc ex1.c


To view assembly (i.e. just run processor and compile to assembler):
gcc -S ex1.c


Emacs
*********
In dired mode, to duplicate a directory...
    C     ;; to copy it, then specify a new name

In C-mode, to compile and run:

    M-Return    ;; First time this runs, give it a command, i.e.:
                ;;   make clean; make ex5; echo; ./ex5;
                ;; On subsequent executions, this will be the default

To generate tags table:

    ctags -e -R   ;; i.e. this works fine for C (outputs file TAGS)
                  ;; you can also run this in /usr/include/ (to get tags table for stdio.h and friends)



C
*******

   Libraries:

      Libraries are a bunch of object files, grouped together in a single file, often by using the ar archiver tool.

      /usr/lib       contains the standard libraries (i.e. libc.so, libc.a, libc.dylib etc..)

      /usr/include   contains header files for the standrad libraries (i.e. stdio.h etc)

      Static libaries have .a extension (i.e. libc.a, libm.a etc).

      Dynamic libaries have .so extension (unix), .dylib (OSX), or .dll (Windows) i.e. libc.so, libc.dylib etc..

      You can see which libraries have been dynamically linked by running:
         ldd <executable>        # on Linux
         otool -L <executable>   # on OSX


Good explanation of pointers:
http://nuclear.mutantstargoat.com/articles/pointers_explained.pdf


Strings are just arrays of chars.
The following are equivalent:

   char *myString = "yay";
   char[] myString = {'y', 'a', 'y', '\0'}; // notice the nul_byte at the end

C treats the computer's memory as one big array.
A pointer is a memory address, with a type specifier.
You can increment/decrement a pointer.
You can use array index notation to get/set values (i.e. pointer[1] = 5).
A pointer gives you raw, direct access to a block of memory.

There are four primary useful things you do with pointers in C code:
1. Ask the OS for a chunk of memory and use a pointer to work with it. This includes strings and something you haven't seen yet, structs.
2. Passing large blocks of memory (like large structs) to functions with a pointer so you don't have to pass the whole thing to them.
3. Taking the address of a function so you can use it as a dynamic callback.
4. Complex scanning of chunks of memory such as converting bytes off a network socket into data structures or parsing files.

For nearly everything else you see people use pointers, they should be using arrays. In the early days of C programming people used pointers to speed up their programs because the compilers were really bad at optimizing array usage. These days the syntax to access an array vs. a pointer are translated into the same machine code and optimized the same, so it's not as necessary. Instead, you go with arrays every time you can, and then only use pointers as a performance optimization if you absolutely have to.

    type *ptr
        "a pointer of type named ptr"

    *ptr
        "the value of whatever ptr is pointed at"

    *(ptr + i)
        "the value of (whatever ptr is pointed at plus i)"

    &thing
        "the address of thing"

    type *ptr = &thing
        "a pointer of type named ptr set to the address of thing"

    ptr++
        "increment where ptr points"

Pointers Are Not Arrays
No matter what, you should never think that pointers and arrays are the same thing. They are not the same thing, even though C lets you work with them in many of the same ways. For example, if you do sizeof(cur_age) in the code above, you would get the size of the pointer, not the size of what it points at. If you want the size of the full array, you have to use the array's name, age as I did on line 12.

The memory location of a struct is a long.
But you can printf it with %p
I.e.    printf("location of myPointer: %p", myPointer);
