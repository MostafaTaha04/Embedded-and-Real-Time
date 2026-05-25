#include "DynamicArray.h"
#include <stdio.h>
#include <stdlib.h>

struct DynamicArray * DynamicArrayCreate( int size, int blockSize){
    if(size <= 0 || blockSize <= 0 || size > MAX_SIZE ){
        return NULL;
    }

    struct DynamicArray *newArray = (struct DynamicArray*)malloc(sizeof(struct DynamicArray));
    if(newArray == NULL){
        return NULL;
    }

    newArray->dArray = (int*)malloc(size * sizeof(int));
    if (newArray->dArray == NULL) {
        free(newArray); 
        return NULL;
    }

    newArray->dArraySize = size;
    newArray->dArrayBlockSize = blockSize;
    newArray->NumOfElements = 0;

    return newArray;
}



void DynamicArrayDestroy( struct DynamicArray *DynaminArrayPtr){
    if (DynaminArrayPtr != NULL) {
        if (DynaminArrayPtr->dArray != NULL) {
            free(DynaminArrayPtr->dArray);
        }
        free(DynaminArrayPtr); 
    }
}


DynamicArrayError DynamicArrayInsert(struct DynamicArray *DynaminArrayPtr, int data){
    
    if(DynaminArrayPtr == NULL || DynaminArrayPtr->dArray == NULL){
        return ERR_NULL_PTR;
    }
    
    if(DynaminArrayPtr->NumOfElements == DynaminArrayPtr->dArraySize){
        int newSize = DynaminArrayPtr->dArraySize + DynaminArrayPtr->dArrayBlockSize;
        int *tempArray = (int*)realloc(DynaminArrayPtr->dArray, newSize * sizeof(int));

        if (tempArray == NULL) {
            return ERR_ALLOCATION_FAILED; 
        }
        DynaminArrayPtr->dArray = tempArray;
        DynaminArrayPtr->dArraySize = newSize;
    }

    DynaminArrayPtr->dArray[DynaminArrayPtr->NumOfElements] = data;
    DynaminArrayPtr->NumOfElements++;

    return OK;
}

DynamicArrayError DynamicArrayDelete(struct DynamicArray *DynaminArrayPtr, int* data) {
    if (DynaminArrayPtr == NULL || data == NULL) {
        return ERR_NULL_PTR;
    }

    if (DynaminArrayPtr->NumOfElements == 0) {
        return ERR_ARRAY_EMPTY;
    }

    DynaminArrayPtr->NumOfElements--;
    *data = DynaminArrayPtr->dArray[DynaminArrayPtr->NumOfElements];
    return OK;
}