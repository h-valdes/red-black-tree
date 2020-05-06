#ifndef RBTREE_H
#define RBTREE_H

#include "stdio.h"
#include "stdlib.h"

typedef enum color_t {
    RED,
    BLACK
} color_t;

typedef void PrintDataFunc_t(void *data);

typedef struct Node {
    int key;
    color_t color;
    void *data;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node_t;

typedef struct RBT_t {
    struct Node *root;
    struct Node *nil;
    PrintDataFunc_t *print_data;
} RBT_t;

// Create a new Red Black Tree
RBT_t *RBT_new(PrintDataFunc_t *printFunc);

// Insert a new node
_Bool RBT_insert(RBT_t *pRBT, int key, void *data);

void RBT_print_data(RBT_t *pRBT, Node_t *pNode);

// Inser fixup
_Bool insert_fixup(RBT_t *pRBT, Node_t *pNode);

// Search for a specific node
Node_t *RBT_search(RBT_t *pRBT, int key);

// Rotation to the left of a node
void left_rotate(RBT_t *pRBT, Node_t *x);

// Rotation to the right of a node
void right_rotate(RBT_t *pRBT, Node_t *x);

// Transplant operation for the node
void transplant(RBT_t *pRBT, Node_t *u, Node_t *v);

// Tree-Minimum
Node_t *tree_minimum(RBT_t *pRBT, Node_t *x);

// Tree-Maximum
Node_t *tree_maximum(RBT_t *pRBT, Node_t *x);

// Delete a node
void RBT_delete(RBT_t *pRBT, Node_t *z);

// Fixup for the delete
void delete_fixup(RBT_t *pRBT, Node_t *x);

// Erase a node
_Bool RBT_erase(Node_t *pRBT, int key);

// Clear the tree
void RBT_clear_tree(RBT_t *pRBT);

// Clear a node
void clear(RBT_t *pRBT, Node_t *pNode);

// Print a specific node
void RBT_print_node(RBT_t *pRBT, Node_t *pNode);

void add_nil(Node_t *pNode, FILE *pFile, int *count);

void add_children(RBT_t *pRBT, Node_t *pNode, FILE *pFile, int *count);

void add_node_color(Node_t *pNode, FILE *pFile);

Node_t *RBT_search(RBT_t *pRBT, int k);

// Generate DOT file for Graphviz
void RBT_export_dot(RBT_t *pRBT);

#endif