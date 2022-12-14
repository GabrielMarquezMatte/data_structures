#include "set_type.h"
#include <stdlib.h>
#include <string.h>

set_t *set_type_create(size_t capacity) {
    set_t *set = (set_t *)malloc(sizeof(set_t));
    set->size = 0;
    set->capacity = capacity;
    set->data = (void **)malloc(capacity * sizeof(void *));
    return set;
}

void set_init_alloc(set_t *set, size_t capacity) {
    set->size = 0;
    set->capacity = capacity;
    set->data = (void **)malloc(capacity * sizeof(void *));
}

void set_type_free(set_t *set) {
    free(set->data);
}

void set_type_add(set_t *set, void *data) {
    if (set->size == set->capacity) {
        set_type_resize(set, set->capacity * 2);
    }
    set->data[set->size++] = data;
}

void set_type_remove(set_t *set, void *data) {
    for (size_t i = 0; i < set->size; i++) {
        if (set->data[i] == data) {
            set->data[i] = set->data[--set->size];
            return;
        }
    }
}

int set_type_contains(set_t *set, void *data) {
    for (size_t i = 0; i < set->size; i++) {
        if (set->data[i] == data) {
            return 1;
        }
    }
    return 0;
}

void set_type_clear(set_t *set) {
    set->size = 0;
}

void set_type_resize(set_t *set, size_t capacity) {
    set->capacity = capacity;
    set->data = (void **)realloc(set->data, capacity * sizeof(void *));
}

void set_type_sort(set_t *set, int (*compare)(const void *, const void *)) {
    qsort(set->data, set->size, sizeof(void *), compare);
}

void set_type_foreach(set_t *set, void (*callback)(void *)) {
    for (size_t i = 0; i < set->size; i++) {
        callback(set->data[i]);
    }
}

void *set_type_get(set_t *set, size_t index) {
    return set->data[index];
}