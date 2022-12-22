#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif
#include "structures.h"
typedef struct
{
    int size;
    string_t *str;
} arguments_t;
int vector_string_test(arguments_t *args)
{
    int size = args->size;
    string_t *result_str = args->str;
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
        if (*value != i)
        {
            string_concat(result_str, "Vector test failed\n");
            return 0;
        }
    }
    vector_free(v);
    free(v);
    string_concat(result_str, "Vector test passed\n");
    return 1;
}
int hash_table_test(arguments_t *args)
{
    int size = args->size;
    string_t *result_str = args->str;
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
        if (*value != i && i != size - 1)
        {
            string_concat(result_str, "Hash table test failed\n");
            return 0;
        }
        else if (*value != 1000 && i == size - 1)
        {
            string_concat(result_str, "Hash table test failed\n");
            return 0;
        }
    }
    hash_table_free(ht);
    free(ht);
    string_concat(result_str, "Hash table test passed\n");
    return 1;
}
int set_test(arguments_t *args)
{
    int size = args->size;
    string_t *result_str = args->str;
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
        if (*value != i)
        {
            string_concat(result_str, "Set test failed\n");
            return 0;
        }
    }
    set_type_free(s);
    free(s);
    string_concat(result_str, "Set test passed\n");
    return 1;
}
int hash_vector_test(arguments_t *args)
{
    int size = args->size;
    string_t *result_str = args->str;
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
        hash_table_insert(ht, &i, v, sizeof(int), sizeof(vector_t));
    }
    for (int i = 0; i < size; i++)
    {
        vector_t *v = hash_table_get(ht, &i, sizeof(int));
        for (int j = 0; j < 10; j++)
        {
            int *value = vector_get(v, j, sizeof(int));
            if (*value != j)
            {
                string_concat(result_str, "Hash vector test failed\n");
                return 0;
            }
        }
    }
    hash_table_free(ht);
    free(ht);
    string_concat(result_str, "Hash vector test passed\n");
    return 1;
}

int binary_tree_test(arguments_t *args)
{
    int size = args->size;
    string_t *result_str = args->str;
    binary_tree *bt = malloc(sizeof(binary_tree));
    binary_tree_init(bt);
    for (int i = 0; i < size; i++)
    {
        binary_tree_insert(bt, &i);
    }
    for (int i = 0; i < size; i++)
    {
        size_t search = binary_tree_search(bt, &i);
        if (search == 0)
        {
            string_concat(result_str, "Binary tree test failed\n");
            return 0;
        }
    }
    binary_tree_free(bt);
    free(bt);
    string_concat(result_str, "Binary tree test passed\n");
    return 1;
}

void create_thread(void *thread_array, void *(*function)(void *), arguments_t *args, int index)
{
#ifdef _WIN32
    ((HANDLE *)thread_array)[index] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)function, (void *)args, 0, NULL);
#else
    pthread_create(&((pthread_t *)thread_array)[index], NULL, function, (void *)args);
#endif
}
int main(int argc, char **argv)
{
    int size = 100;
    int runned = 0;
    if (argc > 1)
    {
        string_t *result_str = malloc(sizeof(string_t));
        string_init_alloc(result_str, 1024 * 1024);
#ifdef _WIN32
        HANDLE *thread_array = malloc(sizeof(HANDLE) * (argc - 2));
#else
        pthread_t *thread_array = malloc(sizeof(pthread_t) * (argc - 2));
#endif
        size = atoi(argv[1]);
        arguments_t *args = malloc(sizeof(arguments_t));
        args->size = size;
        args->str = result_str;
        for (int i = 2; i < argc; i++)
        {
            if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
            {
                printf("Usage: %s size [-v --vector] [--hash] [--set] [--hash_vector] [--binary_tree]\n", argv[0]);
                return 1;
            }
            if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--vector") == 0)
            {
                create_thread(thread_array, (void *)vector_string_test, args, i - 2);
                runned = 1;
            }
            if (strcmp(argv[i], "--hash") == 0)
            {
                create_thread(thread_array, (void *)hash_table_test, args, i - 2);
                runned = 1;
            }
            if (strcmp(argv[i], "--set") == 0)
            {
                create_thread(thread_array, (void *)set_test, args, i - 2);
                runned = 1;
            }
            if (strcmp(argv[i], "--hash_vector") == 0)
            {
                create_thread(thread_array, (void *)hash_vector_test, args, i - 2);
                runned = 1;
            }
            if(strcmp(argv[i], "--binary_tree") == 0)
            {
                create_thread(thread_array, (void *)binary_tree_test, args, i - 2);
                runned = 1;
            }
        }
#ifdef _WIN32
        WaitForMultipleObjects(argc - 2, thread_array, TRUE, INFINITE);
#else
        for (int i = 0; i < argc - 2; i++)
        {
            pthread_join(thread_array[i], NULL);
        }
#endif
#ifdef _WIN32
        for (int i = 0; i < argc - 2; i++)
        {
            CloseHandle(thread_array[i]);
        }
#endif
        free(thread_array);
        string_print(result_str);
        string_free(result_str);
        free(result_str);
        free(args);
    }
    if (!runned)
    {
        printf("Usage: %s size [-v --vector] [--hash] [--set] [--hash_vector] [--binary_tree]\n", argv[0]);
        return 1;
    }
    return 0;
}