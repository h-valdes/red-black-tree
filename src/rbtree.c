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

_Bool RBT_insert_node(Node_t *pRBT, int key, char *data, size_t size){
    return 0;
}

void RBT_clear_tree(RBT_t *pRBT){
    free(pRBT);
}