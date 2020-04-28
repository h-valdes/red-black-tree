#ifndef RBTREE_H
#define RBTREE_H

#include "stdio.h"

enum color_t {BLACK, RED};

typedef struct Node {
    int key;
    enum color_t color;
    struct Node *parent_node;
    struct Node *left_node;
    struct Node *right_node;
} Node_t;

typedef struct RBT_t {
    struct Node *root_node;
} RBT_t;

// Create a new Red Black Tree
RBT_t *RBT_new_tree();

// Insert a new node
_Bool RBT_insert_node(RBT_t *pRBT, int key);

// Inser fixup
_Bool RBT_insert_fixup(RBT_t *pRBT, Node_t *pNode);

// Search for a specific node
Node_t *RBT_search_node(RBT_t *pRBT, int key);

// Get parent of a node
Node_t *RBT_get_parent(RBT_t *pRBT, Node_t *pNode);

// Get Grandparent of a node
Node_t *RBT_get_grandparent(RBT_t *pRBT, Node_t *pNode);

// Get Sibling of a node
Node_t *RBT_get_sibling(RBT_t *pRBT, Node_t *pNode);

// Get uncle of a node
Node_t *RBT_get_uncle(RBT_t *pRBT, Node_t *pNode);

// Rotation to the left of a node
void RBT_left_rotate(RBT_t *pRBT, Node_t *x);

// Rotation to the right of a node
void RBT_right_rotate(RBT_t *pRBT, Node_t *x);

// Erase a node
_Bool RBT_erase_node(Node_t *pRBT, int key);

// Clear the tree
void RBT_clear_tree(RBT_t *pRBT);

// Clear a node
void RBT_clear(Node_t *pNode);

// Print a specific node
void RBT_print_node(RBT_t *pRBT, Node_t *pNode);


#endif