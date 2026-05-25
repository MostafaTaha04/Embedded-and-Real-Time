#include "dll.h"
#include <stdlib.h>

typedef struct Node {
    void* item;
    struct Node* next;
    struct Node* prev;
} Node;

struct List {
    Node head; /* Dummy head */
    Node tail; /* Dummy tail */
    size_t size;
};

List* ListCreate(void) {
    List* list = (List*)malloc(sizeof(List));
    if (!list) return NULL;

    list->head.prev = NULL;
    list->head.next = &list->tail;
    list->head.item = NULL;

    list->tail.prev = &list->head;
    list->tail.next = NULL;
    list->tail.item = NULL;

    list->size = 0;
    return list;
}

void ListDestroy(List** _list, void (*_elementDestroy)(void* _item)) {
    List* list;
    Node* curr;

    if (!_list || !*_list) return;
    list = *_list;
    curr = list->head.next;

    while (curr != &list->tail) {
        Node* next = curr->next;
        if (_elementDestroy && curr->item) {
            _elementDestroy(curr->item);
        }
        free(curr);
        curr = next;
    }

    free(list);
    *_list = NULL;
}

static List_Result InsertBefore(Node* _next, void* _item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return LIST_ALLOCATION_ERROR;

    newNode->item = _item;
    newNode->next = _next;
    newNode->prev = _next->prev;

    _next->prev->next = newNode;
    _next->prev = newNode;

    return LIST_SUCCESS;
}

List_Result ListPushHead(List* _list, void* _item) {
    List_Result res;
    if (!_list || !_item) return LIST_UNINITIALIZED_ERROR;
    res = InsertBefore(_list->head.next, _item);
    if (res == LIST_SUCCESS) _list->size++;
    return res;
}

List_Result ListPushTail(List* _list, void* _item) {
    List_Result res;
    if (!_list || !_item) return LIST_UNINITIALIZED_ERROR;
    res = InsertBefore(&_list->tail, _item);
    if (res == LIST_SUCCESS) _list->size++;
    return res;
}

static List_Result RemoveNode(Node* _node, void** _pItem) {
    *_pItem = _node->item;
    _node->prev->next = _node->next;
    _node->next->prev = _node->prev;
    free(_node);
    return LIST_SUCCESS;
}

List_Result ListPopHead(List* _list, void** _pItem) {
    List_Result res;
    if (!_list || !_pItem) return LIST_UNINITIALIZED_ERROR;
    if (_list->size == 0) return LIST_UNDERFLOW_ERROR;

    res = RemoveNode(_list->head.next, _pItem);
    if (res == LIST_SUCCESS) _list->size--;
    return res;
}

List_Result ListPopTail(List* _list, void** _pItem) {
    List_Result res;
    if (!_list || !_pItem) return LIST_UNINITIALIZED_ERROR;
    if (_list->size == 0) return LIST_UNDERFLOW_ERROR;

    res = RemoveNode(_list->tail.prev, _pItem);
    if (res == LIST_SUCCESS) _list->size--;
    return res;
}

size_t ListSize(const List* _list) {
    if (!_list) return 0;
    return _list->size;
}