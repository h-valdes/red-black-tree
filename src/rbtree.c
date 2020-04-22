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