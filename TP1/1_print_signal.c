#include <string.h>
#include <stdio.h>


int main(void) {
    for (int i = 0; i < 65; ++i)
        printf("%d: %s\n", i, strsignal(i));
    return 0;
}
