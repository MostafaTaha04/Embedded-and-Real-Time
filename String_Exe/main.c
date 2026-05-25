#include <stdio.h>
#include <string.h>   
#include "string.h" 

int main() {
    char testStr1[] = "Hello World";
    char pal1[] = "racecar";
    char pal2[] = "hello";
    char numStr1[] = "-404";
    char numStr2[] = "12abc"; 
    int convertedNum = 0;
    char buffer[MAX_STRING_LENGTH];
    int testNum = -9876;
    int testZero = 0;
    char sentence[] = "cat dog bird";
    char messyString[] = "   hello   world   test  ";
    int wordCount;

    printf("========== STARTING TESTS ==========\n\n");

    /* 1. Testing ReverseStr */
    printf("--- Testing ReverseStr ---\n");
    printf("Original: '%s'\n", testStr1);
    
    if (ReverseStr(testStr1) == OK) {
        printf("Reversed: '%s'\n", testStr1);
    } else {
        printf("Error reversing string.\n");
    }
    printf("\n");

    /* 2. Testing IsPalindrome */
    printf("--- Testing IsPalindrome ---\n");
    printf("Is '%s' a palindrome? ", pal1);
    if (IsPalindrome(pal1) == OK) printf("Yes!\n");
    else printf("No.\n");

    printf("Is '%s' a palindrome? ", pal2);
    if (IsPalindrome(pal2) == OK) printf("Yes!\n");
    else printf("No.\n");
    printf("\n");

    /* 3. Testing MyAToI */
    printf("--- Testing MyAToI ---\n");
    if (MyAToI(numStr1, &convertedNum) == OK) {
        printf("Success! String '%s' is now math integer: %d\n", numStr1, convertedNum);
    }

    if (MyAToI(numStr2, &convertedNum) == ERROR) {
        printf("Correctly caught error for garbage string: '%s'\n", numStr2);
    }
    printf("\n");

    /* 4. Testing MyIToA */
    printf("--- Testing MyIToA ---\n");
    if (MyIToA(testNum, buffer) == OK) {
        printf("Integer %d successfully converted to string: '%s'\n", testNum, buffer);
    }
    
    if (MyIToA(testZero, buffer) == OK) {
        printf("Integer %d successfully converted to string: '%s'\n", testZero, buffer);
    }
    printf("\n");

    /* 5. Testing ReverseWordsInString */
    printf("--- Testing ReverseWordsInString ---\n");
    printf("Original: '%s'\n", sentence);
    
    if (ReverseWordsInString(sentence) == OK) {
        printf("Reversed: '%s'\n", sentence);
    } else {
        printf("Error reversing words.\n");
    }
    printf("\n");

    /* 6. Testing CountWordsInString */
    printf("--- Testing CountWordsInString ---\n");
    printf("String: '%s'\n", messyString);
    
    wordCount = CountWordsInString(messyString);
    if (wordCount != ERROR) {
        printf("Word count: %d\n", wordCount);
    } else {
        printf("Error counting words.\n");
    }
    
    printf("\n========== TESTS COMPLETE ==========\n");
    return 0;
}