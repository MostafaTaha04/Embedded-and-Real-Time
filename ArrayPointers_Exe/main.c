#include <stdio.h>
#include "exercise.h"

/*A quick helper function to print arrays nicely*/
void print_array(int arr[], int size) {
    int i;
    printf("[ ");
    
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

int main() {
    int arr1[] = {4, 1, 2, 2, 2, 3, 4, 2};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int common = most_common(arr1, size1);    
    
    int arr2[] = {3, 8, -5, 2, 7, -4};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int evens = even_odd(arr2, size2);
    
    int arr3[] = {9, 4, 7, 1, 3, 8, 5};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    
    int arr4[] = {1, 0, 1, 1, 0, 0, 1, 0};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    
    printf("--- STARTING TESTS ---\n\n");

    
    /*TEST 1: most_common*/
    printf("Test 1: most_common\n");
    printf("Array: "); 
    print_array(arr1, size1);

    printf("Expected: 2 | Actual: %d\n\n", common);


    /*TEST 2: even_odd*/
    
    printf("Test 2: even_odd (Preserving order)\n");
    printf("Original Array: "); 
    print_array(arr2, size2);
    
    printf("Sorted Array:   "); 
    print_array(arr2, size2);
    printf("Expected evens: 3 | Actual evens: %d\n\n", evens);


    /*TEST 3: ascending_array*/

    printf("Test 3: ascending_array\n");
    printf("Original Array: "); 
    print_array(arr3, size3);
    
    ascending_array(arr3, size3); 
    printf("Sorted Array:   "); 
    print_array(arr3, size3);
    printf("\n");


    /*TEST 4: zeros_first_ones_last*/
    
    printf("Test 4: zeros_first_ones_last\n");
    printf("Original Array: "); 
    print_array(arr4, size4);
    
    zeros_first_ones_last(arr4, size4);
    printf("Sorted Array:   "); 
    print_array(arr4, size4);
    printf("\n");

    printf("--- TESTS COMPLETE ---\n");
    return 0;
}