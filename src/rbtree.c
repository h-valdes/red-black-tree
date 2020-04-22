#include "rbtree.h"
#include <stdlib.h>

RBT_t *RBT_new(){
    RBT_t *pRBT = NULL;
    pRBT = malloc(sizeof(RBT_t));
    if(pRBT != NULL){
        pRBT->root_node = NULL;
    }
    return pRBT;
}

_Bool RBT_insert(Node_t *pRBT, int key, char *data, size_t size){
    return 0;
}

void RBT_delete(RBT_t *pRBT){
    free(pRBT);
}