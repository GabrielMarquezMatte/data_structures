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

void binary_tree_insert(binary_tree *tree, void *data)
{
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    if (!tree->root)
    {
        tree->root = node;
    }
    else
    {
        node_t *current = tree->root;
        while (current)
        {
            if (strcmp(data, current->data) < 0)
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

size_t binary_tree_search(binary_tree *tree, void *data)
{
    node_t *current = tree->root;
    while (current)
    {
        if (strcmp(data, current->data) < 0)
        {
            current = current->left;
        }
        else if (strcmp(data, current->data) > 0)
        {
            current = current->right;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

void binary_tree_delete(binary_tree *tree, void *data)
{
    node_t *current = tree->root;
    while (current)
    {
        if (strcmp(data, current->data) < 0)
        {
            current = current->left;
        }
        else if (strcmp(data, current->data) > 0)
        {
            current = current->right;
        }
        else
        {
            if (current->left && current->right)
            {
                node_t *successor = current->right;
                while (successor->left)
                {
                    successor = successor->left;
                }
                current->data = successor->data;
                current = successor;
            }
            node_t *parent = current->parent;
            node_t *child = current->left ? current->left : current->right;
            if (parent)
            {
                if (parent->left == current)
                {
                    parent->left = child;
                }
                else
                {
                    parent->right = child;
                }
            }
            else
            {
                tree->root = child;
            }
            if (child)
            {
                child->parent = parent;
            }
            free(current);
            break;
        }
    }
}

binary_tree *create_binary_tree()
{
    binary_tree *tree = malloc(sizeof(binary_tree));
    binary_tree_init(tree);
    return tree;
}