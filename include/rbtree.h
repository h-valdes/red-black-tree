#ifndef RBTREE_H
#define RBTREE_H

#include "stdio.h"

enum color_t {BLACK, RED};

typedef struct Node {
    enum color_t color;
    int key;
    size_t size;
    struct Node *parent_node;
    struct Node *left_node;
    struct Node *right_node;
} Node;

typedef struct Tree {
    struct Node *root_node;
} Tree;

#endif