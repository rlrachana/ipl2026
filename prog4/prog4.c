#include <stdio.h>

struct Bitfield {
    unsigned int firstbit : 1;
};

int main() {
    struct Bitfield a;

    a.firstbit = 1;

    printf("The value of a.firstbit is: %u\n", a.firstbit);
    printf("The size of the structure is: %zu byte(s)\n", sizeof(a));

    return 0;
}