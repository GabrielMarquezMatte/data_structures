#include "binary_tree.h"
#include <string.h>
#include <stdlib.h>

void binary_tree_init(binary_tree *tree)
{
    tree->root = NULL;
}

void binary_tree_free(binary_tree *tree)
{
    node_t *node = tree->root;
    while (node)
    {
        if (node->left)
        {
            node = node->left;
        }
        else if (node->right)
        {
            node = node->right;
        }
        else
        {
            node_t *parent = node->parent;
            if (parent)
            {
                if (parent->left == node)
                {
                    parent->left = NULL;
                }
                else
                {
                    parent->right = NULL;
                }
            }
            free(node);
            node = parent;
        }
    }
}

void binary_tree_clear(binary_tree *tree)
{
    binary_tree_free(tree);
    binary_tree_init(tree);
}

void binary_tree_insert(binary_tree *tree, void *data, int (*compare)(void *, void *))
{
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    if (tree->root == NULL)
    {
        tree->root = node;
    }
    else
    {
        node_t *current = tree->root;
        while (current)
        {
            int result = compare(data, current->data);
            if (result < 0)
            {
                if (current->left)
                {
                    current = current->left;
                }
                else
                {
                    current->left = node;
                    node->parent = current;
                    break;
                }
            }
            else
            {
                if (current->right)
                {
                    current = current->right;
                }
                else
                {
                    current->right = node;
                    node->parent = current;
                    break;
                }
            }
        }
    }
}

void binary_tree_remove(binary_tree *tree, void *data, int (*compare)(void *, void *))
{
    node_t *node = binary_tree_find(tree, data, compare);
    if (node)
    {
        binary_tree_remove_node(tree, node);
    }
}

void binary_tree_remove_node(binary_tree *tree, node_t *node)
{
    if (node->left == NULL && node->right == NULL)
    {
        if (node->parent)
        {
            if (node->parent->left == node)
            {
                node->parent->left = NULL;
            }
            else
            {
                node->parent->right = NULL;
            }
        }
        else
        {
            tree->root = NULL;
        }
        free(node);
    }
    else if (node->left == NULL)
    {
        if (node->parent)
        {
            if (node->parent->left == node)
            {
                node->parent->left = node->right;
            }
            else
            {
                node->parent->right = node->right;
            }
        }
        else
        {
            tree->root = node->right;
        }
        node->right->parent = node->parent;
        free(node);
    }
    else if (node->right == NULL)
    {
        if (node->parent)
        {
            if (node->parent->left == node)
            {
                node->parent->left = node->left;
            }
            else
            {
                node->parent->right = node->left;
            }
        }
        else
        {
            tree->root = node->left;
        }
        node->left->parent = node->parent;
        free(node);
    }
    else
    {
        node_t *current = node->right;
        while (current->left)
        {
            current = current->left;
        }
        node->data = current->data;
        binary_tree_remove_node(tree, current);
    }
}

node_t *binary_tree_find(binary_tree *tree, void *data, int (*compare)(void *, void *))
{
    node_t *current = tree->root;
    while (current)
    {
        int result = compare(data, current->data);
        if (result == 0)
        {
            return current;
        }
        else if (result < 0)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return NULL;
}

binary_tree *binary_tree_create()
{
    binary_tree *tree = malloc(sizeof(binary_tree));
    binary_tree_init(tree);
    return tree;
}