#ifndef RBTREE_H
#define RBTREE_H

#include "stdio.h"

enum color_t {BLACK, RED};

typedef struct Node {
    int key;
    enum color_t color;
    char *data;
    size_t size;
    struct Node *parent_node;
    struct Node *left_node;
    struct Node *right_node;
} Node_t;

typedef struct RBT_t {
    struct Node_t *root_node;
} RBT_t;

// Create a new Red Black Tree
RBT_t *RBT_new_tree();

// Insert a new node
_Bool RBT_insert_node(RBT_t *pRBT, int key, char *data, size_t size);

// Search for a specific node
Node_t *RBT_search_node(RBT_t *pRBT, int key);

// Get parent of a node
Node_t *RBT_get_parent(Node_t *pNode);

// Get Grandparent of a node
Node_t *RBT_get_grandparent(Node_t *pNode);

// Get Sibling of a node
Node_t *RBT_get_sibling(Node_t *pNode);

// Get uncle of a node
Node_t *RBT_get_uncle(Node_t *pNode);

// Rotation to the left of a node
void RBT_left_rotate(Node_t *pNode);

// Rotation to the right of a node
void RBT_right_rotate(Node_t *pNode);

// Erase a node
_Bool RBT_erase_node(Node_t *pRBT, int key);

// Clear the tree
void RBT_clear_tree(RBT_t *pRBT);

// Clear a node
void RBT_clear_node(Node_t *pNode);


#endif