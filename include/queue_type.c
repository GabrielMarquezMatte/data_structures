#include "queue_type.h"
#include <stdlib.h>
#include <string.h>

void queue_init(queue_t *q)
{
    q->data = NULL;
    q->size = 0;
    q->capacity = 0;
    q->front = NULL;
    q->back = NULL;
}

void queue_init_alloc(queue_t *q, size_t capacity, size_t size)
{
    q->data = malloc(capacity * size);
    q->size = 0;
    q->capacity = capacity;
    q->front = q->data;
    q->back = q->data;
}

void queue_free(queue_t *q)
{
    free(q->data);
    q->data = NULL;
    q->size = 0;
    q->capacity = 0;
    q->front = NULL;
    q->back = NULL;
}

void queue_clear(queue_t *q)
{
    q->size = 0;
    q->front = q->data;
    q->back = q->data;
}

void queue_push(queue_t *q, void *data, size_t size)
{
    if (q->size == q->capacity)
    {
        q->capacity = q->capacity ? q->capacity * 2 : 1;
        q->data = realloc(q->data, q->capacity * size);
        q->front = q->data;
        q->back = (char *)q->data + q->size * size;
    }
    memcpy(q->back, data, size);
    q->back = (char *)q->back + size;
    q->size++;
}

void queue_pop(queue_t *q, size_t size)
{
    if (q->size == 0)
    {
        return;
    }
    q->front = (char *)q->front + size;
    q->size--;
}

void *queue_front(queue_t *q)
{
    return q->front;
}

void *queue_back(queue_t *q)
{
    return (char *)q->back - q->size;
}

void *queue_get(queue_t *q, size_t index, size_t size)
{
    return (char *)q->front + index * size;
}