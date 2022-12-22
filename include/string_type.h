#pragma once
#include <vcruntime.h>
typedef struct
{
    char *data;
    size_t size;
    size_t capacity;
} string_t;
void string_init(string_t *s);
void string_init_alloc(string_t *s, size_t capacity);
void string_push_back(string_t *s, char c);
void string_free(string_t *s);
void string_clear(string_t *s);
void string_reserve(string_t *s, size_t capacity);
void string_set(string_t *s, char *data, size_t size);
void string_concat(string_t *s, char *data);
void string_print(string_t *s);