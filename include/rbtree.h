#ifndef RBTREE_H
#define RBTREE_H

#include "stdio.h"
#include "stdlib.h"

typedef enum color_t {
    RED,
    BLACK
} color_t;


typedef struct Node {
    int key;
    color_t color;
    void *data;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node_t;

typedef void PrintFunc_t(Node_t *pNode);

typedef struct RBT_t {
    struct Node *root;
    struct Node *null;
    PrintFunc_t *print_fn;
} RBT_t;

/*
Function: print_int
@brief Print the information in a node with data type int
@param *pNode pointer of the node to be printed
*/
void print_int(Node_t *pNode);

/*
Function: print_str
@brief Print the information in a node with data type str
@param *pNode pointer of the node to be printed
*/
void print_str(Node_t *pNode);

/*
Function: RBT_new
@brief Create a new Red Black Tree.
@param *printFunc: function pointer of how to print the data
@return a red black tree pointer
*/
RBT_t *RBT_new(PrintFunc_t *print_fn);

/*
Function: RBT_new_int
@brief Wrapper around the generic constructur RBT_new for the int. 
It assigns an already defined print_int function
*/
RBT_t *RBT_new_int();

/*
Function: RBT_new_str
@brief Wrapper around the generic constructor RBT_new for the str type.
It assigns an already defined print_str function
*/
RBT_t *RBT_new_str();

/*
Function: RBT_insert
@brief Insert a new data into a node.
@param key: Key ID for the new node
@param *data: pointer to the data that is going to be saved
@return
*/
_Bool RBT_insert(RBT_t *pRBT, int key, void *data, size_t data_size);

/*
Function: RBT_print_node
@brief Print the data in a node. Calls the function pointer in the tree.
@param *pRBT: pointer of the tree
@param key: key of the node
*/
void RBT_print_node(RBT_t *pRBT, int key);

/*
Function: insert_fixup
@brief Proof if the new node broke some of the RBT rules than fix the problems.
@param *pRBT: pointer of the tree
@param *pNode: pointer of the node
*/
_Bool insert_fixup(RBT_t *pRBT, Node_t *pNode);

/*
Function: RBT_search
@brief Search for a Node by giving the key
@param *pRBT: pointer of the tree
@param key: key of the node
@return: a node
*/
Node_t *RBT_search(RBT_t *pRBT, int key);

/*
Function: left_rotate
@brief Helper function for delete and insert procedures. Rotate to the left a node in the tree respect to their parents.
@param *pRBT: pointer of the tree
@param *x: pointer of the node to be rotated
*/
void left_rotate(RBT_t *pRBT, Node_t *x);

/*
Function: right_rotate
@brief Helper function for delete and insert procedures. Rotate to the right a node in the tree respect to their parents.
@param *pRBT: pointer of the tree
@param *x: pointer of the node to be rotated
*/
void right_rotate(RBT_t *pRBT, Node_t *x);

// Transplant operation for the node
void transplant(RBT_t *pRBT, Node_t *u, Node_t *v);

/*
Function: tree_minimum
@brief Get the minimum of the subtree for a given node.
@param *pRBT: pointer of the tree
@param *x: pointer of the node
*/
Node_t *tree_minimum(RBT_t *pRBT, Node_t *x);

/*
Function: tree_maximum
@brief Get the maximum of the subtree for a given node.
@param *pRBT: pointer of the tree
@param *x: pointer of the node
*/
Node_t *tree_maximum(RBT_t *pRBT, Node_t *x);

/*
Function: RBT_delete
@brief Delete a node from the tree.
@param *pRBT: pointer of the tree
@param *z: pointer of the node to be deleted
*/
void RBT_delete(RBT_t *pRBT, Node_t *z);

/*
Function: delete_fixup
@brief Helper function of RBT_delete. Checks and fix if there are any broken rules of the tree.
@param *pRBT: pointer of the tree
@param *x: pointer of node to be deleted
*/
void delete_fixup(RBT_t *pRBT, Node_t *x);

/*
Function: RBT_clear_tree
@brief Clear and free the whole tree and nodes
@param *pRBT: pointer of the tree
*/
void RBT_clear_tree(RBT_t *pRBT);

/*
Function: clear
@brief Helper function for RBT_clear_tree. Cleans recursively the nodes
@param *pRBT: pointer of the tree
@param *pNode: pointer of the node
*/
void clear(RBT_t *pRBT, Node_t *pNode);

/*
Function: add_null
@brief Helper function for RBT_export_dot. Adds the null nodes lines into the the DOT File.
@param *pNode: pointer of the node
@param *pFile: pointer of the file stream
@param *count: counter identifier of how many null nodes already exists
*/
void add_null(Node_t *pNode, FILE *pFile, int *count);

/*
Function: add_children
@brief Helper function for RBT_export_dot. Adds every child of the current node and calls add_null if necesary.
@param *pRBT: pointer of the tree
@param *pNode: pointer of the node to be added
@param *pFile: pointer of the file stream
@param *count: counter identifier of how many null nodes already exists
*/
void add_children(RBT_t *pRBT, Node_t *pNode, FILE *pFile, int *count);

/*
Function: add_node_color
@brief Helper function for RBT_export_dot. Adds a new line in the DOT File containing the color of the node.
@param *pNode: pointer of the node
@param *pFile: pointer of the file stream 
*/
void add_node_color(Node_t *pNode, FILE *pFile);

/* 
Function: RBT_export_dot
@brief Export the Red Black Tree into a DOT File for graphviz
@param *pRBT: pointer of the tree
*/
void RBT_export_dot(RBT_t *pRBT);

#endif