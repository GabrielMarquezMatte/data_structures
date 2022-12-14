#pragma once
#include <stdio.h>

typedef struct {
    void *data;
    size_t size;
    size_t capacity;
    void *front;
    void *back;
} queue_t;

void queue_init(queue_t *queue);
void queue_init_alloc(queue_t *q, size_t capacity, size_t size);
void queue_free(queue_t *queue);
void queue_clear(queue_t *queue);
void queue_push(queue_t *queue, void *data);
void queue_pop(queue_t *queue, void *data);
void *queue_front(queue_t *queue);
void *queue_back(queue_t *queue);
void *queue_get(queue_t *queue, size_t index);