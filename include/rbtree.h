#ifndef RBTREE_H
#define RBTREE_H

#include "stdio.h"

enum color_t {BLACK, RED};

typedef const void *GetKeyFunc_t(const void *data);

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
    struct Node *root_node;
    GetKeyFunc_t *getKey;
} RBT_t;

RBT_t *newRBT();

_Bool RBT_insert(Node_t *pRBT, int key, char *data, size_t size);

Node_t RBT_search(Node_t *pRBT, int key);

_Bool RBT_erase(Node_t *pRBT, int key);

void RBT_clear(RBT_t *pRBT);

#endif