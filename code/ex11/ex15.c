#include <stdio.h>

int main(int argc, char *argv[])
{
    // Ok let's try and access some random addresses...
    int a[] = {1, 2, 3};
    int *b = a;
    printf("*b: %d\n\n", *b);
    printf("*(b+1): %d\n\n", *(b+1));
    printf("*(b+2): %d\n\n", *(b+2));

    // try to get address of first element of a
    // And then get a pointer to it...
    // It should be the original element, right? Yes.
    int *c = &(a[0]); // ok
    int d = *c;
    printf("d: %d\n", d);

    // No can do...
    /* int **e = &a; // ok */
    /* int f[] = *e; */
    /* printf("f[0]: %d\n", f[0]); */

    char *people[] = { "Grover", "Elmo", "Bigbird" }; // a pointer to an array of pointers
    char **g = &(people[0]); // Get the address of the first element in the top-level array. It's still a pointer to an array of pointers (hence the **)
    char *h_string = *g;
    char *mmm_string = *(g+1);
    char yay_char = **g;
    char woop_char = **(g+1);
    printf("h_string: %s\n", h_string);
    printf("mmm_string: %s\n", mmm_string);
    printf("yay_char: %c\n", yay_char);
    printf("woop_char: %c\n", woop_char);
    
    // printf("b (address): %d\n\n", b); // compiler allows this, but its doing a cast.
    //printf("*(b+3): %d\n\n", *(b+3)); // compiler allows this, but it's dangerous...
    //printf("*(b+1000): %d\n\n", *(b+1000)); // compiler allows this, but it's dangerous... Can cause a seg fault
    //printf("*(0): %d\n\n", *(0)); // Compiler will not allow this. Operand must have type pointer.
    //printf("*(b - b): %d\n\n", *(b - b)); // Compiler will not allow this.
    //printf("*(b - (int)b): %d\n\n", *(b - (int)b)); // Compiler will allow this, but it will likely seg fault.

    // create two arrays we care about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // Safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // first way using indexing
    for (i = 0; i < count; i++) {
        printf("%s has %d years alive.\n",
               names[i], ages[i]);
    }
    printf("---\n");

    // setup the pointers to the start of the arrays
    int *cur_age = ages; // this has type "pointer to an integer"
    char **cur_name = names; // this has type "pointer to an arrat of chars"

    // second way using pointers
    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
               *(cur_name+i), *(cur_age+i));
    }
    printf("---\n");

    // Ok but can we do the same trick with the array refs? Yes we can.
    for (i = 0; i < count; i++) {
        printf("%s is %d years old. Yayyyy\n",
               *(names+i), *(ages+i));
    }
    printf("---\n");

    // third way, pointers are just arrays
    for (i = 0; i < count; i++) {
        printf("%s is %d years old again.\n",
               cur_name[i], cur_age[i]);
    }
    printf("---\n");

    // fourth way with pointers in a stupid complex way
    for (cur_name = names, cur_age = ages;
         (cur_age - ages) < count;
         /* These are both pointers. Initially they start out equal. */
         /* On each iteration, cur_age is incremented by one. */
         /* So afer count iterations, the difference will be count. */
         cur_name++, cur_age++)
    {
        printf("%s lived %d years so far.\n",
               *cur_name, *cur_age);
    }

    int size = 2;
    int ints_2d[size][size];
    int j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            ints_2d[i][j] = i + j + 7;
        }
    }

    // Ok but why can't we do this with pointers?
    /* int **num_points = ints_2d; */
    /* for (i = 0; i < size; i++) { */
    /*     for (j = 0; j < size; j++) { */
    /*         int num = num_points[i][j]; */
    /*         printf("num[%d][%d]: %d\n", i, j, num); */
    /*     } */
    /* } */
    
    return 0;
}
