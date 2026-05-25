#include <stdio.h>
#include <stdlib.h>
#include "Files.h"
#include "Bit.h"

int main() {
    const char* testFilename = "test_document.txt";
    FILE *tempFile;
    unsigned char x2 = 234; 
    unsigned char y2;
    unsigned char x3 = 167; 
    unsigned char x4 = 170; 
    unsigned char y4 = 167; 
    unsigned int x9 = 43690;
    unsigned int reversed;

    printf("========================================\n");
    printf("       PART 1: FILE OPERATIONS\n");
    printf("========================================\n\n");

    tempFile = fopen(testFilename, "w");
    if (tempFile != NULL) {
        fprintf(tempFile, "Hello World\n");
        fprintf(tempFile, "This is a test file for our C program.\n");
        fprintf(tempFile, "We are counting lines, words, and characters.\n");
        fprintf(tempFile, "Good luck!\n");
        fclose(tempFile);
    }

    printf("--- Testing printLastNLines (Last 2 lines) ---\n");
    printLastNLines(testFilename, 2);
    printf("\n");

    printf("--- Testing printRowsColumnsCharsNumbers ---\n");
    printRowsColumnsCharsNumbers(testFilename);
    printf("\n");

    printf("========================================\n");
    printf("       PART 2: BITWISE OPERATIONS\n");
    printf("========================================\n\n");

    printf("--- Question 2: Invert Bits ---\n");
    invertBits(x2, &y2);
    printf("\n");

    printf("--- Question 3: Rotate Right by 3 ---\n");
    rotateRight(x3, 3);
    printf("\n");

    printf("--- Question 4: Set Bits (n=3, p=6) ---\n");
    setbits(x4, 6, 3, y4);
    printf("\n");

    printf("--- Question 9: Reverse Bits in Integer ---\n");
    printf("Original Integer (Decimal): %u\n", x9);
    reversed = reverseBits(x9);
    printf("Reversed Integer (Decimal): %u\n", reversed);
    printf("\n");

    return 0;
}