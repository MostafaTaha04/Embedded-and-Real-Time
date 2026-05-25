#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "exercise1.h"

void question1 (int a, int b) {
    int sum, dif, mul;

    sum = a + b;
    dif = a - b;
    mul = a * b;

    printf("sum: %d\n", sum);
    printf("dif: %d\n", dif);
    printf("mul: %d\n", mul);
}

int question2 (int N){
    int sum = 1;
    int i;
    for(i = 1; i <= N; i++){
        sum = sum * i;
    }
    return sum;
}

int palindrome (int num){
    int reversed = 0; 
    int remainder; 
    int original = num;
    while (num > 0) {
        remainder = num % 10;
        reversed = reversed * 10 + remainder;
        num /= 10;
    }
    return (original == reversed);
}

int ascendingOrder (int num){
    int lastDigit = 10;
    int currentDigit;
    while (num > 0) {
        int currentDigit = num % 10;
        if (currentDigit > lastDigit) {
            return 0;
        }
        lastDigit = currentDigit;
        num /= 10;
    }
    return 1;
}

int prime (int num){
    int i;

    if(num <= 1){
        return 0;
    }

    for(i = 2; i * i <= num; i++){
        if(num % i == 0){
            return 0;
        }
    }
    return 1;
}

int reverse (int num){
    int reversed = 0;
    while (num != 0) {
        reversed = reversed * 10 + (num % 10);
        num /= 10;
    }
    return reversed;
}

int SamePlace(int base, int check) {
    char sBase[12], sCheck[12];
    int samePlace = 0;
    int diffPlace = 0;
    int i, j, lenBase, lenCheck;
    sprintf(sBase, "%d", base);
    sprintf(sCheck, "%d", check);

    lenBase = strlen(sBase);
    lenCheck = strlen(sCheck);

    if (lenBase != lenCheck)
        return -1;

    for (i = 0; i < lenCheck; i++) {
        for (j = 0; j < lenBase; j++) {
            if (sCheck[i] == sBase[j]) {
                if (i == j) {
                    samePlace++;
                } else {
                    diffPlace++;
                }
            }
        }
    }
    return (samePlace * 10) + diffPlace;
}

int amstrong (int num) {
    int sum = 0, 
    temp = num, 
    digits = 0;

    while (temp > 0) {
        temp /= 10;
        digits++;
    }

    temp = num;
    while (temp > 0) {
        int digit = temp % 10;
        sum += pow(digit, digits);
        temp /= 10;
    }

    return (sum == num);
}