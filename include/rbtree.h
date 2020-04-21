#ifndef RBTREE_H
#define RBTREE_H

typedef struct Node {
    char color;
    size_t size;
    struct node *parent;
    struct node *left_node;
    struct node *right_node;
} Node;

typedef struct Tree {
} Tree;

#endif