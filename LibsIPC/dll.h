#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h>

typedef struct List List;

typedef enum List_Result {
    LIST_SUCCESS = 0,
    LIST_UNINITIALIZED_ERROR,
    LIST_ALLOCATION_ERROR,
    LIST_UNDERFLOW_ERROR
} List_Result;

/* Create a new Doubly Linked List */
List* ListCreate(void);

/* Destroy the list and optionally free elements */
void ListDestroy(List** _list, void (*_elementDestroy)(void* _item));

/* Insert at the head of the list */
List_Result ListPushHead(List* _list, void* _item);

/* Insert at the tail of the list */
List_Result ListPushTail(List* _list, void* _item);

/* Remove from the head of the list */
List_Result ListPopHead(List* _list, void** _pItem);

/* Remove from the tail of the list */
List_Result ListPopTail(List* _list, void** _pItem);

/* Get the number of elements */
size_t ListSize(const List* _list);

#endif /* __DLL_H__ */