#include <stdio.h>
#include "exercise1.h"

void func1(int N, char c){
    int i,j;
    for(i = 0; i <= N; i++){
        for(j = 0; j < i; j++){
            printf("%c", c);
        }
        printf("\n");
    }
}


void func2(int N, char c){
    int i,j;
    for(i=N-1; i >= 0; i--){
        for(j = 0; j <= i; j++){
            printf("%c", c);
        }
        printf("\n");
    }
}



void func3(int N, char c){  
    int i,j;
    for(i = 0; i <= N; i++){
        for(j = 0; j < i; j++){
            printf("%c", c);
        }
        printf("\n");
    }
    for(i = N -1; i > 0; i--){
        for(j = 0; j < i; j++){
            printf("%c", c);
        }
        printf("\n");
    }
}

void func4(int N, char c){
    int i,j;
    for(i = 0; i < N; i++){
        for (j = 0; j < N - i - 1; j++) {
            printf(" ");
        }

        for(j = 0; j <= i; j++){
            printf("%c ", c);
        }
        printf("\n");
    }
}

void func5(int N, char c){
    int i,j;
    
    for(i = N-1; i >= 0; i--){
        for (j = 0; j < N - i - 1; j++) {
            printf(" ");
        }

        for(j = 0; j <= i; j++){
            printf("%c ", c);
        }
        printf("\n");
    }

}

void func6(int N, char c){
    int i,j;
    for(i = 0; i < N; i++){
        for (j = 0; j < N - i - 1; j++) {
            printf(" ");
        }

        for(j = 0; j <= i; j++){
            printf("%c ", c);
        }
        printf("\n");
    }
    for(i = N - 2; i >= 0; i--){
        for (j = 0; j < N - i - 1; j++) {
            printf(" ");
        }

        for(j = 0; j <= i; j++){
            printf("%c ", c);
        }
        printf("\n");
    }
}