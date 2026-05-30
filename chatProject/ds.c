#define _POSIX_C_SOURCE 200809L
#include "ds.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ════════════════════════════════════════
 *  LINKED LIST
 * ════════════════════════════════════════ */

LinkedList *list_create(void) {
    LinkedList *l = malloc(sizeof(LinkedList));
    if (!l) return NULL;
    l->head = NULL;
    l->size = 0;
    return l;
}

void list_destroy(LinkedList *list, void (*free_data)(void *)) {
    ListNode *cur;
    ListNode *tmp;
    if (!list) return;
    cur = list->head;
    while (cur) {
        tmp = cur->next;
        if (free_data) free_data(cur->data);
        free(cur);
        cur = tmp;
    }
    free(list);
}

int list_push_front(LinkedList *list, void *data) {
    ListNode *node = malloc(sizeof(ListNode));
    if (!node) return -1;
    node->data = data;
    node->next = list->head;
    list->head = node;
    list->size++;
    return 0;
}

int list_push_back(LinkedList *list, void *data) {
    ListNode *cur;
    ListNode *node = malloc(sizeof(ListNode));
    if (!node) return -1;
    node->data = data;
    node->next = NULL;
    if (!list->head) {
        list->head = node;
    } else {
        cur = list->head;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }
    list->size++;
    return 0;
}

void *list_pop_front(LinkedList *list) {
    ListNode *node;
    void     *data;
    if (!list || !list->head) return NULL;
    node       = list->head;
    data       = node->data;
    list->head = node->next;
    free(node);
    list->size--;
    return data;
}

void list_remove(LinkedList *list, void *data, int (*cmp)(void *, void *)) {
    ListNode *cur;
    ListNode *prev = NULL;
    if (!list) return;
    cur = list->head;
    while (cur) {
        if (cmp(cur->data, data) == 0) {
            if (prev) prev->next = cur->next;
            else      list->head = cur->next;
            free(cur);
            list->size--;
            return;
        }
        prev = cur;
        cur  = cur->next;
    }
}

ListNode *list_find(LinkedList *list, void *key, int (*cmp)(void *, void *)) {
    ListNode *cur;
    if (!list) return NULL;
    cur = list->head;
    while (cur) {
        if (cmp(cur->data, key) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

int list_size(LinkedList *list) {
    return list ? list->size : 0;
}

/* ════════════════════════════════════════
 *  HASH TABLE
 * ════════════════════════════════════════ */

static unsigned int _hash(const char *key) {
    unsigned int h = 5381;
    while (*key) h = ((h << 5) + h) ^ (unsigned char)*key++;
    return h % HASH_TABLE_SIZE;
}

HashTable *hash_create(void) {
    HashTable *ht = calloc(1, sizeof(HashTable));
    return ht;
}

void hash_destroy(HashTable *ht, void (*free_val)(void *)) {
    int i;
    HashEntry *e;
    HashEntry *tmp;
    if (!ht) return;
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        e = ht->buckets[i];
        while (e) {
            tmp = e->next;
            free(e->key);
            if (free_val) free_val(e->value);
            free(e);
            e = tmp;
        }
    }
    free(ht);
}

int hash_insert(HashTable *ht, const char *key, void *value) {
    unsigned int idx = _hash(key);
    HashEntry   *e   = malloc(sizeof(HashEntry));
    if (!e) return -1;
    e->key   = strdup(key);
    e->value = value;
    e->next  = ht->buckets[idx];
    ht->buckets[idx] = e;
    ht->count++;
    return 0;
}

void *hash_lookup(HashTable *ht, const char *key) {
    unsigned int idx = _hash(key);
    HashEntry   *e   = ht->buckets[idx];
    while (e) {
        if (strcmp(e->key, key) == 0) return e->value;
        e = e->next;
    }
    return NULL;
}

int hash_remove(HashTable *ht, const char *key, void (*free_val)(void *)) {
    unsigned int  idx  = _hash(key);
    HashEntry    *e    = ht->buckets[idx];
    HashEntry    *prev = NULL;
    while (e) {
        if (strcmp(e->key, key) == 0) {
            if (prev) prev->next = e->next;
            else      ht->buckets[idx] = e->next;
            free(e->key);
            if (free_val) free_val(e->value);
            free(e);
            ht->count--;
            return 0;
        }
        prev = e;
        e    = e->next;
    }
    return -1;
}

int hash_count(HashTable *ht) {
    return ht ? ht->count : 0;
}

void hash_foreach(HashTable *ht, void (*cb)(const char *, void *, void *), void *arg) {
    int        i;
    HashEntry *e;
    if (!ht || !cb) return;
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        e = ht->buckets[i];
        while (e) {
            cb(e->key, e->value, arg);
            e = e->next;
        }
    }
}

/* ════════════════════════════════════════
 *  QUEUE
 * ════════════════════════════════════════ */

Queue *queue_create(void) {
    Queue *q = calloc(1, sizeof(Queue));
    return q;
}

void queue_destroy(Queue *q, void (*free_data)(void *)) {
    QueueNode *cur;
    QueueNode *tmp;
    if (!q) return;
    cur = q->head;
    while (cur) {
        tmp = cur->next;
        if (free_data) free_data(cur->data);
        free(cur);
        cur = tmp;
    }
    free(q);
}

int queue_enqueue(Queue *q, void *data) {
    QueueNode *node = malloc(sizeof(QueueNode));
    if (!node) return -1;
    node->data = data;
    node->next = NULL;
    if (!q->tail) {
        q->head = q->tail = node;
    } else {
        q->tail->next = node;
        q->tail       = node;
    }
    q->size++;
    return 0;
}

void *queue_dequeue(Queue *q) {
    QueueNode *node;
    void      *data;
    if (!q || !q->head) return NULL;
    node    = q->head;
    data    = node->data;
    q->head = node->next;
    if (!q->head) q->tail = NULL;
    free(node);
    q->size--;
    return data;
}

void *queue_peek(Queue *q) {
    return (q && q->head) ? q->head->data : NULL;
}

int queue_is_empty(Queue *q) { return !q || q->size == 0; }
int queue_size(Queue *q)     { return q ? q->size : 0; }