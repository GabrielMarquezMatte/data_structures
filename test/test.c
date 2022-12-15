#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "structures.h"
int vector_string_test(int size)
{
    vector_t *v = malloc(sizeof(vector_t));
    vector_init_alloc(v, size, sizeof(int));
    int i;
    for (i = 0; i < size; i++)
    {
        vector_push_back(v, &i, sizeof(int));
    }
    for (i = 0; i < size; i++)
    {
        int *value = vector_get(v, i, sizeof(int));
        if(*value != i)
        {
            fwrite("Vector test failed\n", 1, 19, stdout);
            fflush(stdout);
            return 0;
        }
    }
    vector_free(v);
    free(v);
    fwrite("Vector test passed\n", 1, 19, stdout);
    fflush(stdout);
    return 1;
}
int hash_table_test(int size)
{
    hash_table_t *ht = malloc(sizeof(hash_table_t));
    hash_table_init_alloc(ht, 100);
    int i;
    for (i = 0; i < size; i++)
    {
        hash_table_insert(ht, &i, &i, sizeof(int), sizeof(int));
    }
    i--;
    int j = 1000;
    hash_table_insert(ht, &i, &j, sizeof(int), sizeof(int));
    for (i = 0; i < size; i++)
    {
        int *value = hash_table_get(ht, &i, sizeof(int));
        if(*value != i && i != size - 1)
        {
            fwrite("Hash table test failed\n", 1, 23, stdout);
            fflush(stdout);
            return 0;
        }
        else if(*value != 1000 && i == size - 1)
        {
            fwrite("Hash table test failed\n", 1, 23, stdout);
            fflush(stdout);
            return 0;
        }
    }
    hash_table_free(ht);
    free(ht);
    fwrite("Hash table test passed\n", 1, 23, stdout);
    fflush(stdout);
    return 1;
}
int set_test(int size)
{
    set_t *s = set_type_create(size);
    int i;
    for (i = 0; i < size; i++)
    {
        set_type_add(s, &i);
    }
    i--;
    set_type_add(s, &i);
    for (i = 0; i < size; i++)
    {
        int *value = set_type_get(s, i);
        if(*value != i)
        {
            fwrite("Set test failed\n", 1, 16, stdout);
            fflush(stdout);
            return 0;
        }
    }
    set_type_free(s);
    free(s);
    fwrite("Set test passed\n", 1, 16, stdout);
    fflush(stdout);
    return 1;
}
int hash_vector_test(int size)
{
    hash_table_t *ht = malloc(sizeof(hash_table_t));
    hash_table_init_alloc(ht, size);
    for (int i = 0; i < size; i++)
    {
        vector_t *v = malloc(sizeof(vector_t));
        vector_init_alloc(v, 10, sizeof(int));
        int j;
        for (j = 0; j < 10; j++)
        {
            vector_push_back(v, &j, sizeof(int));
        }
        // The key is going to be Vector_%d
        int size_for_buffer = snprintf(NULL, 0, "Vector_%d", i);
        char *buffer = malloc(size_for_buffer + 1);
        sprintf(buffer, "Vector_%d", i);
        hash_table_insert(ht, buffer, v, strlen(buffer), sizeof(vector_t));
    }
    for (int i = 0; i < size; i++)
    {
        int size_for_buffer = snprintf(NULL, 0, "Vector_%d", i);
        char *buffer = malloc(size_for_buffer + 1);
        sprintf(buffer, "Vector_%d", i);
        vector_t *v = hash_table_get(ht, buffer, strlen(buffer));
        for (int j = 0; j < 10; j++)
        {
            int *value = vector_get(v, j, sizeof(int));
            if(*value != j)
            {
                fwrite("Hash vector test failed\n", 1, 24, stdout);
                fflush(stdout);
                return 0;
            }
        }
    }
    hash_table_free(ht);
    free(ht);
    fwrite("Hash vector test passed\n", 1, 24, stdout);
    fflush(stdout);
    return 1;
}
int main(int argc, char **argv)
{
    int size = 100;
    int runned = 0;
    if (argc > 1)
    {
        HANDLE *thread_array = malloc(sizeof(HANDLE) * (argc - 2));
        size = atoi(argv[1]);
        for (int i = 2; i < argc; i++)
        {
            if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
            {
                printf("Usage: %s size [-v --vector] [--hash] [--set] [--hash_vector]\n", argv[0]);
                return 1;
            }
            if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--vector") == 0)
            {
                thread_array[i - 2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)vector_string_test,(LPVOID)size, 0, NULL);
                runned = 1;
            }
            if (strcmp(argv[i], "--hash") == 0)
            {
                thread_array[i - 2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)hash_table_test,(LPVOID)size, 0, NULL);
                runned = 1;
            }
            if (strcmp(argv[i], "--set") == 0)
            {
                thread_array[i - 2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)set_test,(LPVOID)size, 0, NULL);
                runned = 1;
            }
            if (strcmp(argv[i], "--hash_vector") == 0)
            {
                thread_array[i - 2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)hash_vector_test,(LPVOID)size, 0, NULL);
                runned = 1;
            }
        }
        WaitForMultipleObjects(argc - 2, thread_array, TRUE, INFINITE);
        for(int i = 0; i < argc - 2; i++)
        {
            CloseHandle(thread_array[i]);
        }
        free(thread_array);
    }
    if (!runned)
    {
        printf("Usage: %s [size] [-v --vector] [--hash] [--set] [--hash_vector]\n", argv[0]);
        return 1;
    }
    return 0;
}