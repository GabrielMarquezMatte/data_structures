#pragma once
typedef unsigned __int64 size_t;
typedef struct
{
    void *data;
    size_t size;
    size_t capacity;
} vector_t;
void vector_init(vector_t *v);
void vector_init_alloc(vector_t *v,size_t capacity, size_t size);
void vector_push_back(vector_t *v, void *data, size_t size);
void vector_free(vector_t *v);
void vector_reserve(vector_t *v, size_t capacity, size_t size);
void *vector_get(vector_t *v, size_t index, size_t size);