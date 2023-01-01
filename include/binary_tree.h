#pragma once
#include <stdio.h>

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
} binary_tree;

void binary_tree_init(binary_tree *tree);
void binary_tree_free(binary_tree *tree);
void binary_tree_clear(binary_tree *tree);
void binary_tree_insert(binary_tree *tree, void *data, int (*compare)(const void *,const void *));
void binary_tree_remove(binary_tree *tree, void *data, int (*compare)(const void *,const void *));
void binary_tree_remove_node(binary_tree *tree, node_t *node);
node_t *binary_tree_find(binary_tree *tree, void *data, int (*compare)(const void *,const void *));
binary_tree *binary_tree_create();