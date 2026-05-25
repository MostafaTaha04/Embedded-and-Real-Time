#include "DynamicArray.h"
#include <stdio.h>
#include <string.h>

int checkArray(struct Person arr[], int size){
    if(size > MAX_SIZE || size <= 0){
        return ERR_NULL_PTR;
    }
    if(arr == NULL){
        return ERR_ARRAY_EMPTY;
    }
    return OK;
}


int arrayIDSort(struct Person arr[], int size)
{
    int status;
    int i,j;
    status = checkArray(arr, size);
    if(status != OK){
        return status; 
    }


    for(i = 0; i < size; i++){
        for(j = i+1; j < size; j++){
            if(arr[i].id > arr[j].id){             
                struct Person temp = arr[i]; 
                arr[i] = arr[j];             
                arr[j] = temp;                    
            }
        }
    }
    return OK;
}

int arrayNameSort(struct Person arr[], int size)
{   
    int status;
    int i,j;
    
    status = checkArray(arr, size);
    if(status != OK){
        return status; 
    }

    for(i = 0; i < size; i++){
        for(j = i+1; j < size; j++){
            if(strcmp(arr[i].name, arr[j].name) > 0){             
                struct Person temp = arr[i]; 
                arr[i] = arr[j];             
                arr[j] = temp;                    
            }
        }
    }
    return OK;
}
