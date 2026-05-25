#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int PrintElement(void* _element, size_t _index, void* _context) {
    int* val = (int*)_element;
    printf("Index %lu: %d\n", (unsigned long)_index, *val);
    return 1;
}

void FreeElement(void* _item) {
    free(_item);
}

int main() {
    Vector* myVector;
    int* val;
    void* removedVal;
    size_t i;

    printf("--- Testing Vector Initialization ---\n");
    myVector = VectorCreate(2, 2);
    if (myVector == NULL) {
        printf("Failed to create vector!\n");
        return 1;
    }
    
    printf("Capacity: %lu, Size: %lu\n\n", (unsigned long)VectorCapacity(myVector), (unsigned long)VectorSize(myVector));

    printf("--- Testing Vector Append ---\n");
    for (i = 0; i < 5; ++i) {
        val = (int*)malloc(sizeof(int));
        *val = (i + 1) * 10;
        
        if (VectorAppend(myVector, val) == VECTOR_SUCCESS) {
            printf("Appended %d. New Size: %lu, Capacity: %lu\n", *val, (unsigned long)VectorSize(myVector), (unsigned long)VectorCapacity(myVector));
        }
    }
    printf("\n");

    printf("--- Testing Vector ForEach ---\n");
    VectorForEach(myVector, PrintElement, NULL);
    printf("\n");

    printf("--- Testing Vector Set and Get ---\n");
    val = (int*)malloc(sizeof(int));
    *val = 999;
    VectorSet(myVector, 2, val);
    
    VectorGet(myVector, 2, &removedVal);
    printf("Item at index 2 is now: %d\n\n", *(int*)removedVal);

    printf("--- Testing Vector Remove ---\n");
    while (VectorSize(myVector) > 0) {
        if (VectorRemove(myVector, &removedVal) == VECTOR_SUCCESS) {
            printf("Removed %d. Size: %lu, Capacity: %lu\n", *(int*)removedVal, (unsigned long)VectorSize(myVector), (unsigned long)VectorCapacity(myVector));
            free(removedVal); 
        }
    }
    printf("\n");

    printf("--- Testing Vector Destroy ---\n");
    VectorDestroy(&myVector, NULL); 
    if (myVector == NULL) {
        printf("Vector successfully destroyed and pointer set to NULL.\n");
    }

    return 0;
}