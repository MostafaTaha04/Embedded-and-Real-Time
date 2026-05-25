#include "string.h"
#include <stdio.h>
#include <string.h>

int ReverseStr(char *str){
    int len;
    int i;
    char temp;
    
    if (str == NULL) {
        return ERROR;
    }
    
    len = strlen(str);
    for (i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
    return OK;
}

int IsPalindrome(char *str){
    int len;
    int i;
    
    if (str == NULL) {
        return ERROR;
    }
    
    len = strlen(str);
    for (i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return ERROR;
        }
    }
    return OK;
}

int MyAToI(char *_str, int *num){
    int i = 0;
    int sign = 1;
    int result = 0;
    
    if (_str == NULL || num == NULL) {
        return ERROR;
    }
    
    if (_str[0] == '-') {
        sign = -1;
        i++;
    }
    else if (_str[0] == '+') {
        i++;
    }
    
    for (; _str[i] != '\0'; i++) {
        if (_str[i] < '0' || _str[i] > '9') {
            return ERROR;
        }
        result = result * 10 + (_str[i] - '0');
    }
    
    result = result * sign;
    *num = result;
    return OK;
}

int MyIToA(int _num, char *_buffer){
    int i = 0;
    int isNegative = 0;
    int digit;
    
    if (_buffer == NULL) {
        return ERROR;
    }

    if (_num < 0) {
        isNegative = 1;
    }

    do {
        /* Grab the last digit */ 
        digit = _num % 10;
        
        /* If the number was negative, the digit is negative. Make it positive */ 
        if (digit < 0) {
            digit = -digit; 
        }
        
        _buffer[i++] = digit + '0';
        _num /= 10;
    } while (_num != 0);

    if (isNegative) {
        _buffer[i++] = '-';
    }
    
    _buffer[i] = '\0';
    ReverseStr(_buffer);
    
    return OK;
}

int ReverseWordsInString(char *str){
    int len;
    int start = 0;
    int i, end;
    char temp;
    
    if (str == NULL) {
        return ERROR;
    }
    
    len = strlen(str);
    ReverseStr(str);
    
    for (i = 0; i <= len; i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            end = i - 1;
            while (start < end) {
                temp = str[start];
                str[start] = str[end];
                str[end] = temp;
                start++;
                end--;
            }
            start = i + 1;
        }
    }
    return OK;
}

int CountWordsInString(char *str){
    int count = 0;
    int inWord = 0;
    int i;
    
    if(str == NULL){
        return ERROR;
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            if (!inWord) {
                count++;
                inWord = 1; 
            }
        } else {
            inWord = 0;
        }
    }
    return count;
}