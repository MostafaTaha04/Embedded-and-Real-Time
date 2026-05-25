#include "Bit.h"
#include <stdio.h>

void printBinaryChar(unsigned char val) {
    int i;
    for (i = 7; i >= 0; i--) {
        if (val & (1 << i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
}

int invertBits(unsigned char x, unsigned char *y) {
    if (y == NULL) {
        return ERR;
    }

    *y = ~x;

    printf("x = ");
    printBinaryChar(x);
    printf(" (binary)\n");

    printf("x inverted = ");
    printBinaryChar(*y);
    printf(" (binary)\n");

    return OK;
}

unsigned char rotateRight(unsigned char x, int n) {
    unsigned char rotated;
    n = n % 8; 
    rotated = (x >> n) | (x << (8 - n));

    printf("x = ");
    printBinaryChar(x);
    printf(" (binary)\n");

    printf("x rotated by %d = ", n);
    printBinaryChar(rotated);
    printf(" (binary)\n");

    return rotated;
}

unsigned char setbits(unsigned char x, int p, int n, unsigned char y) {
    unsigned char mask;
    unsigned char y_bits;
    unsigned char x_mask;
    unsigned char x_cleared;
    unsigned char result;

    mask = ~(~0 << n); 
    y_bits = y & mask; 
    x_mask = ~(mask << (p + 1 - n));
    x_cleared = x & x_mask; 
    result = x_cleared | (y_bits << (p + 1 - n));

    printf("x = ");
    printBinaryChar(x);
    printf(" (binary)\n");
    
    printf("y = ");
    printBinaryChar(y);
    printf(" (binary)\n");
    
    printf("setbits n = %d, p = %d gives x = ", n, p);
    printBinaryChar(result);
    printf(" (binary)\n");

    return result;
}

unsigned int reverseBits(unsigned int val) {
    unsigned int numOfBits = sizeof(val) * 8; 
    unsigned int reversed = 0;
    int i;
    unsigned int currentBit;

    for (i = 0; i < numOfBits; i++) {
        currentBit = (val >> i) & 1; 
        reversed |= (currentBit << ((numOfBits - 1) - i)); 
    }

    return reversed;
}