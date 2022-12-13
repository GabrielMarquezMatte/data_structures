#include "hash_table.h"
#include <stdlib.h>

size_t hash_table_hash(void *key, size_t key_size)
{
    size_t hash = 0;
    size_t i;
    for (i = 0; i < key_size; i++)
    {
        hash += ((char *)key)[i];
    }
    return hash;
}

int hash_table_compare(void *key1, void *key2, size_t key_size)
{
    size_t i;
    for (i = 0; i < key_size; i++)
    {
        if (((char *)key1)[i] != ((char *)key2)[i])
        {
            return 0;
        }
    }
    return 1;
}

void hash_table_init_alloc(hash_table_t *ht, size_t capacity)
{
    ht->entries = malloc(sizeof(hash_table_entry_t *) * capacity);
    ht->size = 0;
    ht->capacity = capacity;
    size_t i;
    for (i = 0; i < capacity; i++)
    {
        ht->entries[i] = NULL;
    }
}

void hash_table_free(hash_table_t *ht)
{
    size_t i;
    for (i = 0; i < ht->capacity; i++)
    {
        hash_table_entry_t *entry = ht->entries[i];
        while (entry != NULL)
        {
            hash_table_entry_t *next = entry->next;
            free(entry->key);
            free(entry->value);
            free(entry);
            entry = next;
        }
    }
    free(ht->entries);
}

void hash_table_insert(hash_table_t *ht, void *key, void *value, size_t key_size, size_t value_size)
{
    size_t hash = hash_table_hash(key, key_size);
    size_t index = hash % ht->capacity;
    hash_table_entry_t *entry = ht->entries[index];
    while (entry != NULL)
    {
        if (hash_table_compare(entry->key, key, key_size))
        {
            free(entry->value);
            entry->value = malloc(value_size);
            memcpy(entry->value, value, value_size);
            return;
        }
        entry = entry->next;
    }
    entry = malloc(sizeof(hash_table_entry_t));
    entry->key = malloc(key_size);
    memcpy(entry->key, key, key_size);
    entry->value = malloc(value_size);
    memcpy(entry->value, value, value_size);
    entry->next = ht->entries[index];
    ht->entries[index] = entry;
    ht->size++;
}

void hash_table_remove(hash_table_t *ht, void *key, size_t key_size)
{
    size_t hash = hash_table_hash(key, key_size);
    size_t index = hash % ht->capacity;
    hash_table_entry_t *entry = ht->entries[index];
    hash_table_entry_t *prev = NULL;
    while (entry != NULL)
    {
        if (hash_table_compare(entry->key, key, key_size))
        {
            if (prev == NULL)
            {
                ht->entries[index] = entry->next;
            }
            else
            {
                prev->next = entry->next;
            }
            free(entry->key);
            free(entry->value);
            free(entry);
            ht->size--;
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

void *hash_table_get(hash_table_t *ht, void *key, size_t key_size)
{
    size_t hash = hash_table_hash(key, key_size);
    size_t index = hash % ht->capacity;
    hash_table_entry_t *entry = ht->entries[index];
    while (entry != NULL)
    {
        if (hash_table_compare(entry->key, key, key_size))
        {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}