#include "vector_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vector_init(vector_t *v)
{
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}
void vector_init_alloc(vector_t *v, size_t capacity, size_t size)
{
    v->data = malloc(capacity * size);
    v->size = 0;
    v->capacity = capacity;
}
void vector_push_back(vector_t *v, void *data, size_t size)
{
    if (size <= 0)
    {
		printf("Error: Invalid size\n");
		return;
    }
    if (v->size == v->capacity && v->size > 0)
    {
        v->capacity = v->capacity ? v->capacity * 2 : 1;
        v->data = realloc(v->data, v->capacity * size);
    }
    memcpy((char *)v->data + v->size * size, data, size);
    v->size++;
}
void vector_free(vector_t *v)
{
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}
void vector_clear(vector_t *v)
{
    v->size = 0;
}
void vector_remove(vector_t *v, size_t index, size_t size)
{
    if (index >= v->size)
    {
        return;
    }
    memmove((char *)v->data + index * size, (char *)v->data + (index + 1) * size, (v->size - index - 1) * size);
    v->size--;
}
void vector_reserve(vector_t *v, size_t capacity, size_t size)
{
    if (v->capacity < capacity)
    {
        v->capacity = capacity;
        v->data = realloc(v->data, v->capacity * size);
    }
}
void *vector_get(vector_t *v, size_t index, size_t size)
{
    if (index >= v->size)
    {
        return NULL;
    }
    return (char *)v->data + index * size;
}

void vector_set(vector_t *v, size_t index, void *data, size_t size)
{
    if (index >= v->size)
    {
        return;
    }
    memcpy((char *)v->data + index * size, data, size);
}