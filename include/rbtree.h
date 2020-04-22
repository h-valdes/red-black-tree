#ifndef RBTREE_H
#define RBTREE_H

#include "stdio.h"

enum color_t {BLACK, RED};

typedef struct Node {
    enum color_t color;
    int key;
    size_t size;
    char *data;
    struct Node *parent_node;
    struct Node *left_node;
    struct Node *right_node;
} Node_t;

typedef struct RBT_t {
    struct Node *root_node;
} RBT_t;

RBT_t *newRBT();

_Bool RBT_insert();

void RBT_clear(RBT_t *pRBT);

#endif