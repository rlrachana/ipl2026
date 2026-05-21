#include <stdio.h>

void print_bits(int num) {
    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;
        printf("%d", bit);
        
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int count_ones(int num) {
    int count = 0;
    
    for (int i = 0; i < 32; i++) {
        if (((num >> i) & 1) == 1) {
            count++;
        }
    }
    
    return count;
}

int main() {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);
    
    printf("The bits in %d are: ", n);
    print_bits(n);
    
    int ones = count_ones(n);
    printf("Number of 1 bits: %d\n", ones);
    
    return 0;
}