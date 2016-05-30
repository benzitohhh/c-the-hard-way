# C notes


## To compile a file
```
CFLAGS -Wall gcc ex1.c
```
The `-W` flag is for warnings, so `-Wall` means all warnings.
See `man gcc` for more information (or man `cc` on OSX).

To view assembly (i.e. just run preprocessor and compile to assembler):
```
gcc -S ex1.c
```

To view the preprocessor output
```
gcc -E ex1.c
```

or alternatively
```
cpp ex1.c
```

To output object files (outputs ex1.o, ex2.o etc... i.e. unlinked):

```
gcc -c ex1.c ex2.c
```

To link some existing object files into an executable

```
gcc -o myapp ex1.o ex2.o
```


## Emacs

In dired mode, to duplicate a directory...

```
    C     ;; to copy it, then specify a new name
```

In C-mode, to compile and run:

```
    M-Return    ;; First time this runs, give it a command, i.e.:
                ;;   make clean; make ex5; echo; ./ex5;
                ;; On subsequent executions, this will be the default
```

To generate tags table:

```
    ctags -e -R   ;; i.e. this works fine for C (outputs file TAGS)
                  ;; you can also run this in /usr/include/ (to get tags table for stdio.h and friends)
```


## Object files

Object files (somefile.o) just contain machine code instructions. They are not executable.

To compile an object file:
```
gcc -c somefile.c
```

Multiple object files can be "linked" to create an executable:
```
gcc -o myapp somefile.o someotherfile.o
```

During the linking process, the contents of the object files will be copied into the executable.

Also during linking, any references to external libraries will be "linked".
For example printf calls (header file is in /usr/include/string.h, object file is within library in /usr/lib/libc.so)
will be explicitly linked to.

Note that to compile an object file, any external functions must be defined (otherwise the compiler does not know what to do).

In C, functions can be defined and implemented seperately:

```C
// definition
int myFunction(int a, int b);

// implemention
int myFunction(int a, int b)
{
  return a + b;
}
```

Usually, definitions are put in a seperate header (.h) file. Then the header definitions can be included in any other code that wants to use them, and the implementation library can be linked once.


## Libraries

Libraries are a bunch of object files, grouped together in a single file, often by using the ar archiver tool.

`/usr/lib` contains the standard libraries (i.e. libc.so, libc.a, libc.dylib etc..).

`/usr/include` contains header files for the standrad libraries (i.e. stdio.h etc).

Static libaries have `.a` extension (i.e. libc.a, libm.a etc).

Dynamic libaries have .so extension (unix), .dylib (OSX), or .dll (Windows) i.e. libc.so, libc.dylib etc..

You can see which libraries have been dynamically linked by running:
```
         ldd <executable>        # on Linux
         otool -L <executable>   # on OSX
```

## Pointers

Good explanation of pointers:
http://nuclear.mutantstargoat.com/articles/pointers_explained.pdf

Consider some file `ex5.c`
```
int main(int argc, char *argv[])
{
    // stuff here
}
```

Suppose we call `./ex5 yay oh yes`, when main enters the memory might look
something like this:

| Symbol     | Address | Value  |
|------------|---------|--------|
| argv       | 0x7a70  | 0x7ab0 |
| argv[0]    | 0x7ab0  | 0x7bb0 |
| argv[1]    | 0x7ab8  | 0x7bb6 |
| argv[2]    | 0x7ac0  | 0x7bba |
| argv[3]    | 0x7ac8  | 0x7bbd |
| argv[0][0] | 0x7bb0  | .      |
| argv[0][1] | 0x7bb1  | /      |
| argv[0][2] | 0x7bb2  | e      |
| argv[0][3] | 0x7bb3  | x      |
| argv[0][4] | 0x7bb4  | 5      |
| argv[0][5] | 0x7bb5  | \0     |
| argv[1][0] | 0x7bb6  | y      |
| argv[1][1] | 0x7bb7  | a      |
| argv[1][2] | 0x7bb8  | y      |
| argv[1][3] | 0x7bb9  | \0     |
| argv[2][0] | 0x7bba  | o      |
| argv[2][1] | 0x7bbb  | h      |
| argv[2][2] | 0x7bbc  | \0     |
| argv[3][0] | 0x7bbd  | y      |
| argv[3][1] | 0x7bbe  | e      |
| argv[3][2] | 0x7bbf  | s      |
| argv[3][3] | 0x7bc0  | \0     |

Notice how `argv` is a pointer. It points to a bunch of pointers, where each in turn points to a bunch of chars.

Notice how each pointer takes up 8 bytes of memory.

And how the chars are layed out in a contiguous block of memory (b0 to bf)


## Stack/heap

The processor has some memory locations called registers.

There are some special registers. These include the `program counter` (points to the current instruction in the main memory), `stack pointer` (points to the "top" of the stack), and `base pointer` (points to the previous point in stack just before a function was enterred).

### Stack

The stack is a continuous block of memory set aside for the program.

"Pushing" to the stack involves moving a value from a register onto the top of the stack, and decreasing the stack pointer.
i.e. the higher on the stack, the lower the memory address

"Popping" the stack involves moving a value from the stack into a register, and increasing the stack pointer.

Before jumping to a function's instructions, the arguments for it are pushed onto the stack. Additionally, a space is left in the stack for the return value. And the base pointer is set.

When a function returns, its result is available in the stack where the caller expects it. Also the stack pointer and base pointer are reset, so that the lower addresses on the stack can be reused.

All local variables in C are compiled to instructions that push onto the stack. Likewise, all function arguments are pushed onto the stack.

### Heap

The heap referers to memory that has been dynamically allocated, through system calls such as `malloc`, `realloc`, `calloc` and `free`.

This memory must be explicitly freed after use, otherwise a memory leak occurs.


## Structs

A struct is a complex data type declaration that defines a physicallt grouped list of varaiables to be places under one name in a block of memory, allowing the different variables to be accessed via a single pointer, or the struct declared name which returns the same address.

Struct accessor semantics depends on whether using a pointer or local variable:

```C
#include <stdlib.h>

struct Person {
    int age;
    int height;
};

int main(int argc, char *argv[])
{
    struct Person *p1 = malloc(8); // allocate memory in heap, get a pointer to it
    p1->age = 23; // use the pointer to access a particular address in the heap memory, and write to it

    struct Person p2; // allocate memory on stack, declaring it as a local variable
    p2.age = 28; // access this property of the local variable

    return 0;
}
```
