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

/*
Function: RBT_new
Create a new Red Black Tree.
@param *printFunc: function pointer of how to print the data
return: a red black tree pointer
*/
RBT_t *RBT_new(PrintDataFunc_t *printFunc);

/*
Function: RBT_insert
Insert a new data into a node.
@param key: Key ID for the new node
@param *data: pointer to the data that is going to be saved
returns: 
*/
_Bool RBT_insert(RBT_t *pRBT, int key, void *data);

/*
Function: RBT_print_data
Print the data in a node. Calls the function pointer in the tree.
@param *pRBT: pointer of the tree
@param *pNode: pointer of the node
*/
void RBT_print_data(RBT_t *pRBT, Node_t *pNode);

/*
Function: insert_fixup
Proof if the new node broke some of the RBT rules than fix the problems.
@param *pRBT: pointer of the tree
@param *pNode: pointer of the node
*/
_Bool insert_fixup(RBT_t *pRBT, Node_t *pNode);

/*
Function: RBT_search
Search for a Node by giving the key
@param *pRBT: pointer of the tree
@para key: key of the node
return: a node
*/
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

/*
Function: add_nil
Helper function for RBT_export_dot. Adds the nil nodes lines into
the the DOT File.
@param *pNode: pointer of the node
@param *pFile: pointer of the file stream
@param *count: counter identifier of how many nil nodes already exists
*/
void add_nil(Node_t *pNode, FILE *pFile, int *count);

/*
Function: add_children
Helper function for RBT_export_dot. Adds every child of the current node
and calls add_nil if necesary.
@param *pRBT: pointer of the tree
@param *pNode: pointer of the node to be added
@param *pFile: pointer of the file stream
@param *count: counter identifier of how many nil nodes already exists
*/
void add_children(RBT_t *pRBT, Node_t *pNode, FILE *pFile, int *count);

/*
*Function: add_node_color
Helper function for RBT_export_dot. Adds a new line in the DOT File
containing the color of the node.
@param *pNode: pointer of the node
@param *pFile: pointer of the file stream 
*/
void add_node_color(Node_t *pNode, FILE *pFile);

Node_t *RBT_search(RBT_t *pRBT, int k);

/* 
Function: RBT_export_dot
Export the Red Black Tree into a DOT File for graphviz
@param *pRBT: pointer of the tree
*/
void RBT_export_dot(RBT_t *pRBT);

#endif