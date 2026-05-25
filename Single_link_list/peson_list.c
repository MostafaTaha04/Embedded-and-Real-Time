#include <stddef.h>
#include "person_list.h"

Person* ListInsertHead(Person* _head, Person* _p) {
    if (_p == NULL) {
        return _head;
    }

    _p->m_next = _head;

    return _p;
}

Person* ListRemoveHead(Person* _head, Person** _item) {
    if (_head == NULL || _item == NULL) {
        if (_item != NULL) {
            *_item = NULL;
        }
        return _head; 
    }

    *_item = _head;

    _head = _head->m_next;

    (*_item)->m_next = NULL;

    return _head;
}

Person* ListInsertByKey(Person* _head, int _key, Person* _p) {
    Person* current = _head;

    if (_p == NULL) {
        return _head;
    }

    _p->m_id = _key;

    if (_head == NULL || _head->m_id >= _key) {
        _p->m_next = _head;
        return _p; 
    }

    while (current->m_next != NULL && current->m_next->m_id < _key) {
        current = current->m_next;
    }

    _p->m_next = current->m_next;
    current->m_next = _p;

    return _head;
}

Person* ListRemoveByKey(Person* _head, int _key, Person** _p) {
    Person* current = _head;

    if (_head == NULL || _p == NULL) {
        if (_p != NULL) {
            *_p = NULL;
        }
        return _head;
    }

    if (_head->m_id == _key) {
        *_p = _head;
        _head = _head->m_next;
        (*_p)->m_next = NULL;
        return _head;
    }

    while (current->m_next != NULL && current->m_next->m_id != _key) {
        current = current->m_next;
    }

    if (current->m_next != NULL) {
        *_p = current->m_next;
        current->m_next = current->m_next->m_next; 
        (*_p)->m_next = NULL; 
    } else {
        *_p = NULL;
    }

    return _head;
}

Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p) {

    if (_p == NULL) {
        return _head;
    }
    _p->m_id = _key;

    if (_head == NULL || _head->m_id >= _key) {
        _p->m_next = _head;
        return _p;
    }


    _head->m_next = ListInsertByKeyRec(_head->m_next, _key, _p);
    
    return _head;
}

Person* ListRemoveByKeyRec(Person* _head, int _key, Person** _p) {
    if (_head == NULL) {
        if (_p != NULL) {
            *_p = NULL;
        }
        return NULL;
    }

    if (_head->m_id == _key) {
        Person* nextNode = _head->m_next;
        
        if (_p != NULL) {
            *_p = _head;
            (*_p)->m_next = NULL;
        }
        
        return nextNode; 
    }
    _head->m_next = ListRemoveByKeyRec(_head->m_next, _key, _p);
    
    return _head;
}