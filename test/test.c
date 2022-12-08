#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
void billion_allocations()
{
    vector_t *v = malloc(sizeof(vector_t));
    vector_init_alloc(v, 1e9, sizeof(int));
    for(int i = 0; i < 1e9; i++)
    {
        vector_push_back(v, &i, sizeof(int));
    }
    vector_free(v);
    free(v);
    printf("Billion allocations test passed\n");
}
int main()
{
    vector_t *v = malloc(sizeof(vector_t));
    vector_init_alloc(v, 100, sizeof(int));
    int i;
    for (i = 0; i < 100; i++)
    {
        vector_push_back(v, &i, sizeof(int));
    }
    string_t *result_str = malloc(sizeof(string_t));
    string_init_alloc(result_str,1024*1024);
    for (i = 0; i < 100; i++)
    {
        int *value = vector_get(v, i, sizeof(int));
        char buffer[22];
        sprintf(buffer, "vector[%d] = %d\n", i, *value);
        string_concat(result_str, buffer, strlen(buffer));
    }
    string_print(result_str);
    vector_free(v);
    free(v);
    string_free(result_str);
    free(result_str);
    billion_allocations();
    return 0;
}