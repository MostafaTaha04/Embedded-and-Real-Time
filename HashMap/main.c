#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashMap.h"

/* =========================================================================
   User-Provided Callback Functions
   ========================================================================= */

size_t StringHash(void* _key) {
    unsigned char* str = (unsigned char*)_key;
    size_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; 
    }
    return hash;
}

int StringEqual(void* _firstKey, void* _secondKey) {
    return strcmp((char*)_firstKey, (char*)_secondKey) == 0;
}

int PrintKeyValue(const void* _key, void* _value, void* _context) {
    /* Suppress unused parameter warning */
    (void)_context;
    
    printf("  [Key]: %-10s | [Value]: %d\n", (char*)_key, *(int*)_value);
    return 1; 
}

void DestroyValue(void* _value) {
    if (_value) {
        free(_value);
    }
}

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
    /* C90 requires ALL variable declarations at the top of the block */
    HashMap* map;
    int* duplicateVal;
    Map_Result res;
    void* foundValue = NULL;
    void *removedKey = NULL, *removedVal = NULL;
    size_t iterations;
#ifndef NDEBUG
    Map_Stats stats;
#endif

    printf("--- HashMap Test Program ---\n\n");

    /* 1. Create the Map */
    map = HashMap_Create(10, StringHash, StringEqual);
    if (!map) {
        printf("Failed to create map.\n");
        return 1;
    }
    printf("-> Map successfully created.\n");

    /* 2. Insert items */
    printf("\n--- Inserting Items ---\n");
    HashMap_Insert(map, "Apple", AllocateInt(100));
    HashMap_Insert(map, "Banana", AllocateInt(200));
    HashMap_Insert(map, "Cherry", AllocateInt(300));
    HashMap_Insert(map, "Date", AllocateInt(400));
    /* Cast size_t to unsigned long for C90 %lu support */
    printf("Current Map Size: %lu\n", (unsigned long)HashMap_Size(map));

    /* 3. Test Duplicate Insertion */
    duplicateVal = AllocateInt(999);
    res = HashMap_Insert(map, "Apple", duplicateVal);
    if (res == MAP_KEY_DUPLICATE_ERROR) {
        printf("Correctly prevented duplicate key insertion for 'Apple'.\n");
        free(duplicateVal); 
    }

    /* 4. Find an Item */
    printf("\n--- Finding Items ---\n");
    if (HashMap_Find(map, "Banana", &foundValue) == MAP_SUCCESS) {
        printf("Found 'Banana' - Value is: %d\n", *(int*)foundValue);
    } else {
        printf("Failed to find 'Banana'.\n");
    }

    /* 5. Remove an Item */
    printf("\n--- Removing Items ---\n");
    if (HashMap_Remove(map, "Cherry", &removedKey, &removedVal) == MAP_SUCCESS) {
        printf("Successfully removed 'Cherry' (Value was: %d).\n", *(int*)removedVal);
        free(removedVal); 
    }
    printf("Current Map Size after removal: %lu\n", (unsigned long)HashMap_Size(map));

    /* 6. Iterate using ForEach */
    printf("\n--- Iterating over remaining map ---\n");
    iterations = HashMap_ForEach(map, PrintKeyValue, NULL);
    printf("Total items iterated: %lu\n", (unsigned long)iterations);

    /* 7. Statistics */
#ifndef NDEBUG
    printf("\n--- Map Statistics ---\n");
    stats = HashMap_GetStatistics(map);
    printf("Number of Buckets: %lu\n", (unsigned long)stats.numberOfBuckets);
    printf("Number of Chains:  %lu\n", (unsigned long)stats.numberOfChains);
    printf("Max Chain Length:  %lu\n", (unsigned long)stats.maxChainLength);
#endif

    /* 8. Destroy the map */
    printf("\n--- Destroying Map ---\n");
    HashMap_Destroy(&map, NULL, DestroyValue);
    
    if (map == NULL) {
        printf("Map successfully destroyed and pointer set to NULL.\n");
    }

    return 0;
}