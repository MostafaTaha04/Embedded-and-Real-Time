#ifndef __PERSON_LIST_H__
#define __PERSON_LIST_H__

/* Node struct definition as provided in the presentation */
typedef struct Person Person;

struct Person {
    int     m_id;         /* Primary Key */
    char    m_name[128];
    int     m_age;
    Person* m_next;
};

/**
 * @brief Inserts a new Person node at the head of the list.
 * @param _head - The current head of the list.
 * @param _p - The pre-allocated Person node to insert.
 * @return Person* - The new head of the list.
 */
Person* ListInsertHead(Person* _head, Person* _p);

/**
 * @brief Removes the Person node at the head of the list.
 * @param _head - The current head of the list.
 * @param _item - Pointer to a variable that will receive the removed node.
 * @return Person* - The new head of the list.
 */
Person* ListRemoveHead(Person* _head, Person** _item);

/**
 * @brief Inserts a new Person node into the list, keeping it sorted by the key (m_id).
 * @param _head - The current head of the list.
 * @param _key - The key (m_id) to sort by.
 * @param _p - The pre-allocated Person node to insert.
 * @return Person* - The head of the list (might change if inserted at the beginning).
 */
Person* ListInsertByKey(Person* _head, int _key, Person* _p);

/**
 * @brief Removes a Person node from the list by matching its key (m_id).
 * @param _head - The current head of the list.
 * @param _key - The key (m_id) to search for and remove.
 * @param _p - Pointer to a variable that will receive the removed node.
 * @return Person* - The head of the list (might change if the head was removed).
 */
Person* ListRemoveByKey(Person* _head, int _key, Person** _p);

/**
 * @brief Inserts a new Person node into the list recursively, keeping it sorted.
 * @param _head - The current head of the list.
 * @param _key - The key (m_id) to sort by.
 * @param _p - The pre-allocated Person node to insert.
 * @return Person* - The head of the list.
 */
Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p);

/**
 * @brief Removes a Person node from the list recursively by matching its key.
 * @param _head - The current head of the list.
 * @param _key - The key (m_id) to search for and remove.
 * @param _p - Pointer to a variable that will receive the removed node.
 * @return Person* - The head of the list.
 */
Person* ListRemoveByKeyRec(Person* _head, int _key, Person** _p);

#endif /* __PERSON_LIST_H__ */