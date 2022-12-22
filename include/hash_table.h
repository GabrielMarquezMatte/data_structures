#pragma once
#include <vcruntime.h>
typedef struct hash_table_entry
{
    void *key;
    void *value;
    struct hash_table_entry *next;
} hash_table_entry_t;
typedef struct hash_table
{
    hash_table_entry_t **entries;
    size_t size;
    size_t capacity;
} hash_table_t;

void hash_table_init_alloc(hash_table_t *ht, size_t capacity);
void hash_table_free(hash_table_t *ht);
void hash_table_clear(hash_table_t *ht);
void hash_table_insert(hash_table_t *ht, void *key, void *value, size_t key_size, size_t value_size);
void hash_table_remove(hash_table_t *ht, void *key, size_t key_size);
void *hash_table_get(hash_table_t *ht, void *key, size_t key_size);