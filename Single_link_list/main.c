#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person_list.h"

/* Utility function to dynamically allocate and initialize a new Person */
Person* CreatePerson(int _id, const char* _name, int _age) {
    Person* p = (Person*)malloc(sizeof(Person));
    if (p != NULL) {
        p->m_id = _id;
        /* Safely copy the string to prevent buffer overflows */
        strncpy(p->m_name, _name, sizeof(p->m_name) - 1);
        p->m_name[sizeof(p->m_name) - 1] = '\0'; 
        p->m_age = _age;
        p->m_next = NULL;
    }
    return p;
}

/* Print utility from the API list to visualize the linked list */
void PrintList(Person* _head) {
    Person* current = _head;
    
    printf("Current List:\n");
    if (current == NULL) {
        printf("  [Empty List]\n\n");
        return;
    }
    
    while (current != NULL) {
        printf("  [ID: %d | Name: %s | Age: %d] -> \n", current->m_id, current->m_name, current->m_age);
        current = current->m_next;
    }
    printf("  NULL\n\n");
}

int main() {
    Person* head = NULL;
    Person* removedItem = NULL;
    
    Person* p1;
    Person* p2;
    Person* p3;
    Person* p4;

    printf("--- Testing Single Linked List ---\n\n");

    /* 1. Create some test data */
    p1 = CreatePerson(10, "Alice", 25);
    p2 = CreatePerson(50, "Bob", 30);
    p3 = CreatePerson(20, "Charlie", 22);
    p4 = CreatePerson(5, "Diana", 28); 

    /* 2. Test ListInsertByKey (Should automatically sort as 10 -> 20 -> 50) */
    printf("Inserting Alice (10), Bob (50), and Charlie (20) BY KEY...\n");
    head = ListInsertByKey(head, p1->m_id, p1);
    head = ListInsertByKey(head, p2->m_id, p2);
    head = ListInsertByKey(head, p3->m_id, p3);
    PrintList(head);

    /* 3. Test ListInsertHead (Should force Diana to the front regardless of sorting) */
    printf("Inserting Diana (5) directly at the HEAD...\n");
    head = ListInsertHead(head, p4);
    PrintList(head);

    /* 4. Test ListRemoveByKey (Let's remove Charlie, ID 20) */
    printf("Removing Charlie (ID: 20) BY KEY...\n");
    head = ListRemoveByKey(head, 20, &removedItem);
    if (removedItem != NULL) {
        printf("  Successfully removed: %s\n\n", removedItem->m_name);
        free(removedItem); /* Don't forget to free removed items! */
        removedItem = NULL;
    }
    PrintList(head);

    /* 5. Test ListRemoveHead (Should remove Diana) */
    printf("Removing the HEAD node...\n");
    head = ListRemoveHead(head, &removedItem);
    if (removedItem != NULL) {
        printf("  Successfully removed: %s\n\n", removedItem->m_name);
        free(removedItem);
        removedItem = NULL;
    }
    PrintList(head);

    /* 6. Clean up remaining nodes to prevent memory leaks */
    printf("Cleaning up remaining list...\n");
    while (head != NULL) {
        head = ListRemoveHead(head, &removedItem);
        free(removedItem);
    }
    
    printf("Cleanup complete. Program exiting.\n");

    return 0;
}