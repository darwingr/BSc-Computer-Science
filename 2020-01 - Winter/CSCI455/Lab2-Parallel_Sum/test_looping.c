#include <stdio.h>

void test_looping() {
    int i, f;
    for (i=0; i<10; i++)
        f = 0;

    printf("i = %i, expected 10\n", i);
}

int main() {
    test_looping();
    return 0;
}
