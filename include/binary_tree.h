#pragma once
#include <stdio.h>

typedef struct node {
    void *data;
    struct node *left;
    struct node *right;
    size_t level;
} node;

typedef struct binary_tree {
    node *root;
    size_t height;
    size_t size;
} binary_tree;

binary_tree *create_binary_tree();
void binary_tree_init(binary_tree *tree);
void binary_tree_insert(binary_tree *tree, void *data);
size_t binary_tree_search(binary_tree *tree, void *data);
void binary_tree_delete(binary_tree *tree, void *data);
void binary_tree_free(binary_tree *tree);
void binary_tree_clear(binary_tree *tree);