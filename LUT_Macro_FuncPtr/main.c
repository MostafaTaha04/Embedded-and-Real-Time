#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Ass.h"

int sort_desc(int a, int b) {
    return a < b;
}

int sort_asc(int a, int b) {
    return a > b;
}

int sort_abs(int a, int b) {
    return abs(a) > abs(b);
}

int sort_evens_first(int a, int b) {
    int a_is_even = (a % 2 == 0);
    int b_is_even = (b % 2 == 0);
    
    if (!a_is_even && b_is_even) return 1; 
    if (a_is_even && !b_is_even) return 0; 
    return a > b; 
}

void print_array(int *arr, int size) {
    int i; 
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int *arr1, *arr2;
    int i, size;
    clock_t start, end;
    double time_func, time_macro;
    const char *my_str = "bad"; 
    unsigned char bw_comp[10] = {0};
    CharPair bf_comp[10] = {{0, 0}};
    int test_arr[] = {15, -4, 2, 8, -1, 3, 10};

    printf("=== Part 1: Sorting Time Measurement ===\n");
    
    arr1 = (int*)malloc(Array_size * sizeof(int));
    arr2 = (int*)malloc(Array_size * sizeof(int));
    
    if (!arr1 || !arr2) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    srand((unsigned int)time(NULL));
    for (i = 0; i < Array_size; i++) {
        arr1[i] = rand() % 80000;
    }
    memcpy(arr2, arr1, Array_size * sizeof(int));

    printf("Sorting %d elements with Function...\n", Array_size);
    start = clock();
    swap_with_func(arr1, Array_size);
    end = clock();
    time_func = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sorting %d elements with MACRO...\n", Array_size);
    start = clock();
    sort_with_macro(arr2, Array_size);
    end = clock();
    time_macro = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Time (Function): %f seconds\n", time_func);
    printf("Time (MACRO):    %f seconds\n", time_macro);
    
    free(arr1);
    free(arr2);

    printf("\n=== Part 2: String Compression ===\n");
    
    compress_bitwise(my_str, bw_comp);
    printf("Bitwise:  Byte 0 = 0x%02X, Byte 1 = 0x%02X\n", bw_comp[0], bw_comp[1]);

    compress_bitfield(my_str, bf_comp);
    printf("Bitfield: Byte 0 (L:%d, R:%d), Byte 1 (L:%d, R:%d)\n", 
           bf_comp[0].left, bf_comp[0].right, bf_comp[1].left, bf_comp[1].right);

    printf("\n=== Part 3: Generic Sort with Function Pointers ===\n");
    
    size = sizeof(test_arr) / sizeof(test_arr[0]);

    printf("Original:        ");
    print_array(test_arr, size);

    generic_bubble_sort(test_arr, size, sort_desc);
    printf("1. Descending:   ");
    print_array(test_arr, size);

    generic_bubble_sort(test_arr, size, sort_asc);
    printf("2. Ascending:    ");
    print_array(test_arr, size);

    generic_bubble_sort(test_arr, size, sort_abs);
    printf("3. Abs Value:    ");
    print_array(test_arr, size);

    generic_bubble_sort(test_arr, size, sort_evens_first);
    printf("4. Evens First:  ");
    print_array(test_arr, size);

    return 0;
}