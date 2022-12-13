#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
void vector_string_test(){
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
}
void hash_table_test(){
    hash_table_t *ht = malloc(sizeof(hash_table_t));
    hash_table_init_alloc(ht, 100);
    int i;
    for (i = 0; i < 100; i++)
    {
        hash_table_insert(ht, &i, &i, sizeof(int), sizeof(int));
    }
    i = 99;
    int j = 1000;
    hash_table_insert(ht, &i, &j, sizeof(int), sizeof(int));
    string_t* result_str = malloc(sizeof(string_t));
    string_init_alloc(result_str,1024*1024);
    for (i = 0; i < 100; i++)
    {
        int *value = hash_table_get(ht, &i, sizeof(int));
        char buffer[33];
        sprintf(buffer, "hash_table[%d] = %d\n", i, *value);
        string_concat(result_str, buffer, strlen(buffer));
    }
    string_print(result_str);
    string_free(result_str);
    free(result_str);
    hash_table_free(ht);
    free(ht);
}
int main()
{
    // vector_string_test();
    hash_table_test();
    return 0;
}