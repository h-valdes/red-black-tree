#include "rbtree.h"
#include <stdlib.h>

RBT_t *RBT_new_tree(){
    RBT_t *pRBT = NULL;
    pRBT = malloc(sizeof(RBT_t));
    if(pRBT != NULL){
        pRBT->root_node = NULL;
    }
    return pRBT;
}

Node_t *RBT_get_parent(Node_t *pNode){
    Node_t *parent;
    if(pNode != NULL) {
        parent = pNode->parent_node;
        if(parent == NULL){
            printf("There is no parent\n");
        }
    } else {
        printf("GET PARENT: Node is NULL\n");
    }
    return parent;
}

Node_t *RBT_get_grandparent(Node_t *pNode){
    Node_t *parent;
    Node_t *grandparent;
    if(pNode != NULL){
        parent = RBT_get_parent(pNode);
        if(parent != NULL) {
            grandparent = RBT_get_parent(parent);
            if(grandparent == NULL){
                printf("There is no grand parent\n");
            }
        }
    } else {
        printf("GET GRANDPARENT: Node is NULL\n");
    }
    return grandparent;
}

_Bool RBT_insert_node(RBT_t *pRBT, int key, char *data, size_t size){
    return 0;
}

void RBT_clear_tree(RBT_t *pRBT){
    free(pRBT);
}