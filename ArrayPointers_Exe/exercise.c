#include "exercise.h"
#include <stddef.h>
/*
needed to fix to ues pointer where it should be the most common element is 1 for example
and it could return 1 for an error so we need to separte it
*/
int most_common(int arr[], int size)
{
    int mostCommon = arr[0];
    int maxCount = 1;
    int i;
    int j;

    if (arr == NULL || size <= 0)
    {
        return ERR;
    }
    
    for (i = 0; i < size; i++)
    {
        int count = 1;
        for(j = i + 1; j < size; j++){
            if(arr[i] == arr[j]){
                count++;
            }
        }
        if(count > maxCount){
            maxCount = count;
            mostCommon = arr[i];
        }
    }
    return mostCommon;
}


int even_odd(int arr[], int size)
{
    int evenPosition = 0;
    int i;
    int evenIndex;
    int shiftIndex;

    if (arr == NULL || size <= 0)
    {
        return ERR;
    }

    for(i = 0; i < size; i++){
        if (arr[i] % 2 == 0)
        {
           evenIndex = arr[i];
           for (shiftIndex = i; shiftIndex > evenPosition; shiftIndex--)
            {
                arr[shiftIndex] = arr[shiftIndex - 1];
            }
            arr[evenPosition] = evenIndex;
            evenPosition++;
        }
    
    }
    return evenPosition;
}



void ascending_array(int arr[], int size)
{
    int i;
    int swapped;
    if (arr == NULL || size <= 0){
        return;
    }

    for (i = 0; i < size; i++)
    {   
        int j;
        swapped = 0;
        for(j = 0; j < size - i - 1; j++){ /*Bubble sort every run the last element is in the right place*/ 
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0)
        {
            break;
        }
    }
}

void zeros_first_ones_last(int arr[], int size)
{
    
    int i;
    int j;
    
    if (arr == NULL || size <= 0 || (arr[0] != 0 && arr[0] != 1)){
        return;
    }

    for (i = 0; i < size; i++)
    {
        for(j = 0; j < size - i - 1; j++){ /* Bubble sort every run the last element is in the right place */
            if(arr[j] == 1 && arr[j+1] == 0){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
