#include "string_type.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void string_init(string_t *s)
{
    s->data = NULL;
    s->size = 0;
    s->capacity = 0;
}
void string_init_alloc(string_t *s, size_t capacity)
{
    s->data = malloc(capacity);
    s->size = 0;
    s->capacity = capacity;
}
void string_push_back(string_t *s, char c)
{
    if (s->size == s->capacity)
    {
        s->capacity = s->capacity ? s->capacity * 2 : 1;
        s->data = realloc(s->data, s->capacity);
    }
    s->data[s->size] = c;
    s->size++;
}
void string_free(string_t *s)
{
    free(s->data);
    s->data = NULL;
    s->size = 0;
    s->capacity = 0;
}
void string_clear(string_t *s)
{
    s->size = 0;
}
void string_reserve(string_t *s, size_t capacity)
{
    if (s->capacity < capacity)
    {
        s->capacity = capacity;
        s->data = realloc(s->data, s->capacity);
    }
}
void string_set(string_t *s, char *data, size_t size)
{
    string_reserve(s, size + 1);
    memcpy(s->data, data, size);
    s->data[size] = '\0';
    s->size = size;
}
void string_concat(string_t *s, char *data)
{
    size_t size = strlen(data);
    string_reserve(s, (s->size + size) * 2);
    memcpy(s->data + s->size, data, size);
    s->size += size;
    s->data[s->size] = '\0';
}
void string_print(string_t *s)
{
    fwrite(s->data, s->size, 1, stdout);
    fflush(stdout);
}