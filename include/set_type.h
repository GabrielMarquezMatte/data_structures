#pragma once
#include <vcruntime.h>
typedef struct set_t
{
    size_t size;
    size_t capacity;
    void **data;
} set_t;

set_t *set_type_create(size_t capacity);
void set_init_alloc(set_t *set, size_t capacity);
void set_type_free(set_t *set);
void set_type_add(set_t *set, void *data);
void set_type_remove(set_t *set, void *data);
int set_type_contains(set_t *set, void *data);
void set_type_clear(set_t *set);
void set_type_resize(set_t *set, size_t capacity);
void set_type_sort(set_t *set, int (*compare)(const void *, const void *));
void set_type_foreach(set_t *set, void (*callback)(void *));
void *set_type_get(set_t *set, size_t index);