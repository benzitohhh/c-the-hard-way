#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i = 0;

    while(i < 100) {
        printf("%d: Start sleeping...\n", i);
        usleep(3000000);
        printf("%d: ...Finished sleeping\n", i);
        i++;
    }

    return 0;
}
