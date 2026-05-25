#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DynamicArray.h" 

void printDynamicArray(struct DynamicArray *arr) {
    if (arr == NULL || arr->dArray == NULL) {
        printf("Array is empty or NULL.\n");
        return;
    }
    printf("Elements (%d/%d): [ ", arr->NumOfElements, arr->dArraySize);
    int i;
    for (i = 0; i < arr->NumOfElements; i++) {
        printf("%d ", arr->dArray[i]);
    }
    printf("]\n");
}


void printPeople(struct Person arr[], int size) {
    int i;
    for(i = 0; i < size; i++) {
        printf("{ID: %d, Name: %s} ", arr[i].id, arr[i].name);
    }
    printf("\n");
}

int main() {
    printf("======================================\n");
    printf("   TESTING QUESTION 4 (DYNAMIC ARRAY)\n");
    printf("======================================\n");

    printf("1. Creating Dynamic Array (Size: 2, BlockSize: 2)...\n");
    struct DynamicArray *myArray = DynamicArrayCreate(2, 2);
    if (myArray == NULL) {
        printf("FAILED to create array!\n");
        return 1;
    }
    printf("SUCCESS! Array created.\n\n");


    printf("2. Inserting 5 elements (10, 20, 30, 40, 50)...\n");
    int i;
    for (i = 1; i <= 5; i++) {
        DynamicArrayError status = DynamicArrayInsert(myArray, i * 10);
        if (status == OK) {
            printf("Inserted %d successfully. ", i * 10);
            printDynamicArray(myArray);
        } else {
            printf("FAILED to insert %d. Error code: %d\n", i * 10, status);
        }
    }
    
    printf("\n3. Deleting the last element...\n");
    int deletedVal = 0;
    DynamicArrayError delStatus = DynamicArrayDelete(myArray, &deletedVal);
    if (delStatus == OK) {
        printf("SUCCESS! Deleted value: %d\n", deletedVal);
        printDynamicArray(myArray);
    } else {
        printf("FAILED to delete. Error code: %d\n", delStatus);
    }

    printf("\n4. Destroying array and freeing memory...\n");
    DynamicArrayDestroy(myArray);
    printf("SUCCESS! Memory freed.\n\n");


    printf("======================================\n");
    printf("     TESTING QUESTION 1 (PERSON SORT)\n");
    printf("======================================\n");

    struct Person myClass[3] = {
        {103, "Zack"},
        {101, "Alice"},
        {102, "Bob"}
    };
    int classSize = 3;

    printf("Original Array:\n");
    printPeople(myClass, classSize);

    printf("\nSorting by ID...\n");
    if (arrayIDSort(myClass, classSize) == OK) {
        printPeople(myClass, classSize);
    } else {
        printf("Error during ID Sort!\n");
    }

    printf("\nSorting by Name...\n");
    if (arrayNameSort(myClass, classSize) == OK) {
        printPeople(myClass, classSize);
    } else {
        printf("Error during Name Sort!\n");
    }

    printf("\nAll tests completed! Great job.\n");
    return 0;
}