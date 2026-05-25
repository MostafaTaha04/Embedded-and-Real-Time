#include "HashMap.h"
#include <stdlib.h>

/* =========================================================================
   Internal Data Structures
   ========================================================================= */

typedef struct Node {
    void* key;
    void* value;
    struct Node* next;
} Node;

struct HashMap {
    Node** buckets;
    size_t capacity;
    size_t size;
    HashFunction hashFunc;
    EqualityFunction keysEqualFunc;
};

/* =========================================================================
   Helper Functions
   ========================================================================= */

/* Helper to check if a number is prime (Returns 1 for true, 0 for false) */
static int IsPrime(size_t _num) {
    size_t i;
    if (_num <= 1) return 0;
    if (_num <= 3) return 1;
    if (_num % 2 == 0 || _num % 3 == 0) return 0;
    for (i = 5; i * i <= _num; i += 6) {
        if (_num % i == 0 || _num % (i + 2) == 0) return 0;
    }
    return 1;
}

/* Helper to get the next nearest prime number */
static size_t GetNextPrime(size_t _num) {
    if (_num <= 2) return 2;
    while (!IsPrime(_num)) {
        _num++;
    }
    return _num;
}

/* =========================================================================
   API Implementation
   ========================================================================= */

HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc) {
    HashMap* map;
    
    if (_capacity == 0 || !_hashFunc || !_keysEqualFunc) {
        return NULL;
    }

    map = (HashMap*)malloc(sizeof(HashMap));
    if (!map) {
        return NULL;
    }

    map->capacity = GetNextPrime(_capacity);
    map->size = 0;
    map->hashFunc = _hashFunc;
    map->keysEqualFunc = _keysEqualFunc;
    
    map->buckets = (Node**)calloc(map->capacity, sizeof(Node*));
    if (!map->buckets) {
        free(map);
        return NULL;
    }

    return map;
}

void HashMap_Destroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value)) {
    HashMap* map;
    size_t i;

    if (!_map || !*_map) {
        return;
    }

    map = *_map;

    for (i = 0; i < map->capacity; ++i) {
        Node* curr = map->buckets[i];
        while (curr) {
            Node* next = curr->next;
            
            if (_keyDestroy && curr->key) {
                _keyDestroy(curr->key);
            }
            if (_valDestroy && curr->value) {
                _valDestroy(curr->value);
            }
            
            free(curr);
            curr = next;
        }
    }

    free(map->buckets);
    free(map);
    *_map = NULL;
}

Map_Result HashMap_Rehash(HashMap *_map, size_t newCapacity) {
    size_t newCap;
    Node** newBuckets;
    size_t i;

    if (!_map) {
        return MAP_UNINITIALIZED_ERROR;
    }

    newCap = GetNextPrime(newCapacity);
    newBuckets = (Node**)calloc(newCap, sizeof(Node*));
    if (!newBuckets) {
        return MAP_ALLOCATION_ERROR;
    }

    for (i = 0; i < _map->capacity; ++i) {
        Node* curr = _map->buckets[i];
        while (curr) {
            Node* next = curr->next;
            size_t newIndex = _map->hashFunc(curr->key) % newCap;
            
            curr->next = newBuckets[newIndex];
            newBuckets[newIndex] = curr;
            
            curr = next;
        }
    }

    free(_map->buckets);
    _map->buckets = newBuckets;
    _map->capacity = newCap;

    return MAP_SUCCESS;
}

Map_Result HashMap_Insert(HashMap* _map, const void* _key, const void* _value) {
    size_t index;
    Node* curr;
    Node* newNode;

    if (!_map) return MAP_UNINITIALIZED_ERROR;
    if (!_key) return MAP_KEY_NULL_ERROR;

    index = _map->hashFunc((void*)_key) % _map->capacity;
    curr = _map->buckets[index];

    while (curr) {
        if (_map->keysEqualFunc((void*)_key, curr->key)) {
            return MAP_KEY_DUPLICATE_ERROR;
        }
        curr = curr->next;
    }

    newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return MAP_ALLOCATION_ERROR;

    newNode->key = (void*)_key;
    newNode->value = (void*)_value;
    newNode->next = _map->buckets[index];
    _map->buckets[index] = newNode;

    _map->size++;

    return MAP_SUCCESS;
}

Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue) {
    size_t index;
    Node* curr;
    Node* prev = NULL;

    if (!_map) return MAP_UNINITIALIZED_ERROR;
    if (!_searchKey) return MAP_KEY_NULL_ERROR;
    if (!_pKey || !_pValue) return MAP_UNINITIALIZED_ERROR;

    index = _map->hashFunc((void*)_searchKey) % _map->capacity;
    curr = _map->buckets[index];

    while (curr) {
        if (_map->keysEqualFunc((void*)_searchKey, curr->key)) {
            if (prev) {
                prev->next = curr->next;
            } else {
                _map->buckets[index] = curr->next;
            }

            *_pKey = curr->key;
            *_pValue = curr->value;
            
            free(curr);
            _map->size--;

            return MAP_SUCCESS;
        }
        prev = curr;
        curr = curr->next;
    }

    return MAP_KEY_NOT_FOUND_ERROR;
}

Map_Result HashMap_Find(const HashMap* _map, const void* _key, void** _pValue) {
    size_t index;
    Node* curr;

    if (!_map) return MAP_UNINITIALIZED_ERROR;
    if (!_key) return MAP_KEY_NULL_ERROR;
    if (!_pValue) return MAP_UNINITIALIZED_ERROR;

    index = _map->hashFunc((void*)_key) % _map->capacity;
    curr = _map->buckets[index];

    while (curr) {
        if (_map->keysEqualFunc((void*)_key, curr->key)) {
            *_pValue = curr->value;
            return MAP_SUCCESS;
        }
        curr = curr->next;
    }

    return MAP_KEY_NOT_FOUND_ERROR;
}

size_t HashMap_Size(const HashMap* _map) {
    if (!_map) return 0;
    return _map->size; 
}

size_t HashMap_ForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context) {
    size_t count = 0;
    size_t i;

    if (!_map || !_action) return 0;

    for (i = 0; i < _map->capacity; ++i) {
        Node* curr = _map->buckets[i];
        while (curr) {
            count++;
            if (_action(curr->key, curr->value, _context) == 0) {
                return count; 
            }
            curr = curr->next;
        }
    }

    return count;
}

#ifndef NDEBUG
Map_Stats HashMap_GetStatistics(const HashMap* _map) {
    Map_Stats stats = {0, 0, 0, 0};
    size_t i;
    
    if (!_map) return stats;

    stats.numberOfBuckets = _map->capacity;

    for (i = 0; i < _map->capacity; ++i) {
        Node* curr = _map->buckets[i];
        if (curr) {
            size_t currentChainLength = 0;
            stats.numberOfChains++;
            
            while (curr) {
                currentChainLength++;
                curr = curr->next;
            }
            
            if (currentChainLength > stats.maxChainLength) {
                stats.maxChainLength = currentChainLength;
            }
        }
    }

    if (stats.numberOfChains > 0) {
        stats.averageChainLength = _map->size / stats.numberOfChains;
    }

    return stats;
}
#endif /* NDEBUG */