#include "exercise1.h"
#include <stdio.h>

int main() {
    int choice, a, b, n, i, result, triangleType;
    char c;


    while (1) {
        printf("\n--- Choose an Exercise to Test (1-8) or 0 to Exit ---\n");
        printf("1. Sum/Difference/Multiply [Ex 1]\n");
        printf("2. Factorial of N [Ex 2]\n");
        printf("3. Palindrome Check [Ex 3]\n");
        printf("4. Ascending Order Check [Ex 4]\n");
        printf("5. Prime Number Check [Ex 5]\n");
        printf("6. Reverse Number [Ex 6]\n");
        printf("7. Same Place (Mastermind) [Ex 7]\n");
        printf("8. Armstrong Numbers (0-999) [Ex 8]\n");
        printf("9. Print Triangles [Ex 9]\n");
        printf("Selection: ");
        
        if (scanf("%d", &choice) != 1) break;
        if (choice == 0) break;

        switch (choice) {
            case 1: 
                printf("Enter two integers (a b): ");
                scanf("%d %d", &a, &b);
                question1(a, b);
                break;
            case 2:
                printf("Enter N: ");
                scanf("%d", &n);
                printf("Factorial: %d\n", question2(n));
                break;
            case 3: 
                printf("Enter number: ");
                scanf("%d", &n);
                printf("Result: %d\n", palindrome(n));
                break;
            case 4: 
                printf("Enter number: ");
                scanf("%d", &n);
                printf("Result: %d\n", ascendingOrder(n));
                break;
            case 5: 
                printf("Enter number: ");
                scanf("%d", &n);
                printf("Result: %d\n", prime(n));
                break;
            case 6:
                printf("Enter number: ");
                scanf("%d", &n);
                printf("Reversed: %d\n", reverse(n));
                break;
            case 7:
                printf("Enter base and check numbers: ");
                scanf("%d %d", &a, &b);
                result = SamePlace(a, b);
                printf("Result: %d\n", result);
                break;
            case 8:
                printf("Enter a number to check if it is Armstrong: ");
                scanf("%d", &n);
                if (amstrong(n)) {
                    printf("%d is an Armstrong number!\n", n);
                } else {
                    printf("%d is NOT an Armstrong number.\n", n);
                }
                printf("Armstrong numbers in range 0-999: ");
                for (i = 0; i <= 999; i++) {
                    if (amstrong(i)) printf("%d ", i);
                }
                printf("\n");
                break;
            case 9:
                printf("\n--- Triangles Menu ---\n");
                printf("Enter height (N) and character to print: ");
                
                scanf("%d %c", &n, &c);
                printf("Select triangle type (1-6): ");
                scanf("%d", &triangleType);
                
                switch(triangleType) {
                    case 1: func1(n, c); break; 
                    case 2: func2(n, c); break; 
                    case 3: func3(n, c); break; 
                    case 4: func4(n, c); break; 
                    case 5: func5(n, c); break; 
                    case 6: func6(n, c); break; 
                    default: printf("Invalid triangle type!\n");
                }
                break;
            default:
                printf("Invalid selection!\n");
        }
    }
    return 0;
}