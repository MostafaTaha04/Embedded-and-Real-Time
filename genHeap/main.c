#include <stdio.h>
#include <stdlib.h>
#include "genvec.h"
#include "genHeap.h"

/* =========================================================================
   User-Provided Callback Functions
   ========================================================================= */

/* * Comparator for a MAX-HEAP. 
 * If left < right, returns a negative number, meaning right should bubble up.
 */
int IntMaxComparator(const void* _left, const void* _right) {
    int leftVal = *(const int*)_left;
    int rightVal = *(const int*)_right;
    return leftVal - rightVal;
}

/* Action function to print integers during ForEach */
int PrintIntAction(const void* _elem, void* _context) {
    /* Suppress unused parameter warning */
    (void)_context;
    
    printf("%d ", *(const int*)_elem);
    return 1; /* Return 1 to continue iterating */
}

/* Cleanup function to free the dynamically allocated integers */
void DestroyInt(void* _item) {
    if (_item) {
        free(_item);
    }
}

/* Helper function to allocate an integer on the heap */
int* AllocateInt(int val) {
    int* newInt = (int*)malloc(sizeof(int));
    if (newInt) {
        *newInt = val;
    }
    return newInt;
}

/* =========================================================================
   Main Test Program
   ========================================================================= */

int main(void) {
    /* C90 Strict: All declarations at the top */
    Vector* vec;
    Heap* heap;
    const void* peekedVal;
    void* extractedVal;
    size_t count;

    printf("--- Generic Heap & Vector Test Program ---\n\n");

    /* 1. Create the Vector (Capacity 5, Block Size 5 for dynamic resizing) */
    vec = VectorCreate(5, 5);
    if (!vec) {
        printf("Failed to create vector.\n");
        return 1;
    }
    printf("-> Vector successfully created.\n");

    /* 2. Create the Heap wrapper around the Vector */
    heap = HeapBuild(vec, IntMaxComparator);
    if (!heap) {
        printf("Failed to build heap.\n");
        VectorDestroy(&vec, DestroyInt);
        return 1;
    }
    printf("-> Heap successfully built.\n");

    /* 3. Insert Elements */
    printf("\n--- Inserting Elements (50, 30, 80, 10, 90, 20) ---\n");
    HeapInsert(heap, AllocateInt(50));
    HeapInsert(heap, AllocateInt(30));
    HeapInsert(heap, AllocateInt(80));
    HeapInsert(heap, AllocateInt(10));
    HeapInsert(heap, AllocateInt(90));
    HeapInsert(heap, AllocateInt(20));
    
    /* Note: Casting size_t to unsigned long for C90 compatibility */
    printf("Current Heap Size: %lu\n", (unsigned long)HeapSize(heap));

    /* 4. Peek at the top element */
    peekedVal = HeapPeek(heap);
    if (peekedVal) {
        printf("\nPeek at Top (Should be 90): %d\n", *(const int*)peekedVal);
    }

    /* 5. Iterate over the underlying array */
    printf("\n--- Underlying Array State (Level-Order) ---\n");
    printf("Elements: ");
    count = HeapForEach(heap, PrintIntAction, NULL);
    printf("\nTotal iterated: %lu\n", (unsigned long)count);

    /* 6. Extract elements one by one */
    printf("\n--- Extracting Elements ---\n");
    extractedVal = HeapExtract(heap);
    if (extractedVal) {
        printf("Extracted: %d\n", *(int*)extractedVal);
        DestroyInt(extractedVal); /* We own it now, so we must free it */
    }

    extractedVal = HeapExtract(heap);
    if (extractedVal) {
        printf("Extracted: %d\n", *(int*)extractedVal);
        DestroyInt(extractedVal); 
    }

    printf("Heap Size after extraction: %lu\n", (unsigned long)HeapSize(heap));

    /* 7. Destroy the Heap and Vector */
    printf("\n--- Destroying Heap and Vector ---\n");
    
    /* HeapDestroy un-wraps the vector, freeing the heap struct but returning the vector */
    vec = HeapDestroy(&heap);
    if (heap == NULL) {
        printf("Heap wrapper successfully destroyed.\n");
    }

    /* VectorDestroy frees the array and all remaining items inside it */
    VectorDestroy(&vec, DestroyInt);
    if (vec == NULL) {
        printf("Vector and remaining elements successfully destroyed.\n");
    }

    return 0;
}