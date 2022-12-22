#pragma once
#include <vcruntime.h>

typedef struct node_t
{
    void *data;
    struct node_t *left;
    struct node_t *right;
    struct node_t *parent;
} node_t;

typedef struct binary_tree
{
    node_t *root;
    size_t height;
    size_t size;
} binary_tree;

void binary_tree_init(binary_tree *tree);
void binary_tree_free(binary_tree *tree);
void binary_tree_clear(binary_tree *tree);
void binary_tree_insert(binary_tree *tree, void *data);
size_t binary_tree_search(binary_tree *tree, void *data);
void binary_tree_delete(binary_tree *tree, void *data);
binary_tree *create_binary_tree();