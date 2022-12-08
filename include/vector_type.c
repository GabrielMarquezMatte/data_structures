#include "vector_type.h"
void vector_init(vector_t *v)
{
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}
void vector_init_alloc(vector_t *v,size_t capacity, size_t size)
{
    v->data = malloc(capacity * size);
    v->size = 0;
    v->capacity = capacity;
}
void vector_push_back(vector_t *v, void *data, size_t size)
{
    if (v->size == v->capacity)
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