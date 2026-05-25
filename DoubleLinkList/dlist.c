#include "dlist.h" 
#include <stdlib.h> 
#include <assert.h> 


typedef struct Node {
    void* m_data;
    struct Node* m_next;
    struct Node* m_prev;
} Node;


struct List {
    Node m_head; 
    Node m_tail; 
};


List* ListCreate(void) 
{
    List* list = (List*)malloc(sizeof(List));
    if (!list) {
        return NULL;
    }

    list->m_head.m_data = NULL;
    list->m_head.m_prev = NULL;
    list->m_head.m_next = &list->m_tail;

    list->m_tail.m_data = NULL;
    list->m_tail.m_prev = &list->m_head;
    list->m_tail.m_next = NULL;

    return list;
}

void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item)) 
{
    if (!_pList || !*_pList) {
        return;
    }

    List* list = *_pList;
    Node* current = list->m_head.m_next;


    while (current != &list->m_tail) {
        Node* temp = current;
        current = current->m_next;
        
        if (_elementDestroy && temp->m_data) {
            _elementDestroy(temp->m_data);
        }
        free(temp);
    }

    free(list);
    *_pList = NULL;
}

ListItr ListPushHead(List* _list, void* _item) 
{
    if (!_list) {
        return NULL;
    }
    return ListItrInsertBefore(_list->m_head.m_next, _item);
}

ListItr ListPushTail(List* _list, void* _item) 
{
    if (!_list) {
        return NULL;
    }
    return ListItrInsertBefore(&_list->m_tail, _item);
}

void* ListPopHead(List* _list) 
{
    if (!_list || ListIsEmpty(_list)) {
        return NULL;
    }
    return ListItrRemove(_list->m_head.m_next);
}

void* ListPopTail(List* _list) 
{
    if (!_list || ListIsEmpty(_list)) {
        return NULL;
    }
    return ListItrRemove(_list->m_tail.m_prev);
}

ListItr ListItrBegin(const List* _list) 
{
    if (!_list) {
        return NULL;
    }

    return (ListItr)_list->m_head.m_next;
}

ListItr ListItrEnd(const List* _list) 
{
    if (!_list) {
        return NULL;
    }

    return (ListItr)&_list->m_tail;
}

ListItr ListItrNext(ListItr _itr) 
{
    Node* node = (Node*)_itr;
    if (!node || node->m_next == NULL) {
        return _itr; 
    }
    return (ListItr)node->m_next;
}

ListItr ListItrPrev(ListItr _itr) 
{
    Node* node = (Node*)_itr;
    if (!node) {
        return NULL;
    }
    
    if (node->m_prev && node->m_prev->m_prev == NULL) {
        return _itr; 
    }
    return (ListItr)node->m_prev;
}


void* ListItrGet(ListItr _itr) 
{
    Node* node = (Node*)_itr;
    if (!node || !node->m_prev || !node->m_next) {
        return NULL;
    }
    return node->m_data;
}

void* ListItrSet(ListItr _itr, void* _element) 
{
    Node* node = (Node*)_itr;
    if (!node || !node->m_prev || !node->m_next) {
        return NULL;
    }
    
    void* oldData = node->m_data;
    node->m_data = _element;
    return oldData;
}

ListItr ListItrInsertBefore(ListItr _itr, void* _element) 
{
    Node* current = (Node*)_itr;
    Node* newNode = NULL;

    if (!current || !current->m_prev) {
        return NULL;
    }

    newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }

    newNode->m_data = _element;
    newNode->m_next = current;
    newNode->m_prev = current->m_prev;

    current->m_prev->m_next = newNode;
    current->m_prev = newNode;

    return (ListItr)newNode;
}

void* ListItrRemove(ListItr _itr) 
{
    Node* current = (Node*)_itr;
    void* data = NULL;

    if (!current || !current->m_prev || !current->m_next) {
        return NULL;
    }

    data = current->m_data;

    current->m_prev->m_next = current->m_next;
    current->m_next->m_prev = current->m_prev;

    free(current);
    return data;
}

size_t ListSize(const List* _list) 
{
    size_t count = 0;
    Node* current = NULL;

    if (!_list) {
        return 0;
    }

    current = _list->m_head.m_next;
    while (current != &_list->m_tail) {
        count++;
        current = current->m_next;
    }

    return count;
}

size_t ListIsEmpty(List* _list) 
{
    if (!_list) {
    }
    return (_list->m_head.m_next == &_list->m_tail) ? 1 : 0;
}

ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context) 
{
    Node* current = (Node*)_begin;
    Node* endNode = (Node*)_end;

    if (!current || !endNode || !_action) {
        return _begin;
    }

    while (current != endNode) {
        if (_action(current->m_data, _context) == 0) {
            break;
        }
        current = current->m_next;
    }

    return (ListItr)current;
}