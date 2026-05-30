#ifndef DS_H
#define DS_H

#include <stddef.h>

/* ════════════════════════════════════════
 *  LINKED LIST
 * ════════════════════════════════════════ */
typedef struct ListNode {
    void           *data;
    struct ListNode *next;
} ListNode;

typedef struct {
    ListNode *head;
    int       size;
} LinkedList;

LinkedList *list_create(void);
void        list_destroy(LinkedList *list, void (*free_data)(void *));
int         list_push_front(LinkedList *list, void *data);
int         list_push_back(LinkedList *list, void *data);
void       *list_pop_front(LinkedList *list);
void        list_remove(LinkedList *list, void *data, int (*cmp)(void *, void *));
ListNode   *list_find(LinkedList *list, void *key, int (*cmp)(void *, void *));
int         list_size(LinkedList *list);

/* ════════════════════════════════════════
 *  HASH TABLE
 * ════════════════════════════════════════ */
#define HASH_TABLE_SIZE 64

typedef struct HashEntry {
    char            *key;
    void            *value;
    struct HashEntry *next;     /* chaining */
} HashEntry;

typedef struct {
    HashEntry *buckets[HASH_TABLE_SIZE];
    int        count;
} HashTable;

HashTable *hash_create(void);
void       hash_destroy(HashTable *ht, void (*free_val)(void *));
int        hash_insert(HashTable *ht, const char *key, void *value);
void      *hash_lookup(HashTable *ht, const char *key);
int        hash_remove(HashTable *ht, const char *key, void (*free_val)(void *));
int        hash_count(HashTable *ht);
/* iterate: calls cb(key, value, arg) for every entry */
void       hash_foreach(HashTable *ht,
                        void (*cb)(const char *, void *, void *),
                        void *arg);

/* ════════════════════════════════════════
 *  QUEUE  (used for free multicast IPs)
 * ════════════════════════════════════════ */
typedef struct QueueNode {
    void             *data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *head;
    QueueNode *tail;
    int        size;
} Queue;

Queue *queue_create(void);
void   queue_destroy(Queue *q, void (*free_data)(void *));
int    queue_enqueue(Queue *q, void *data);
void  *queue_dequeue(Queue *q);
void  *queue_peek(Queue *q);
int    queue_is_empty(Queue *q);
int    queue_size(Queue *q);

#endif /* DS_H */