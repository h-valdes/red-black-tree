#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    RBT_t *intTree = RBT_new(INT);
    RBT_insert(intTree, 3, &(int){10});
    RBT_insert(intTree, 4, &(int){15});

    Node_t *x = RBT_search(intTree, 3); // Search a node
    RBT_print_data(intTree, x);

    if(x != intTree->nil) {
        printf("Node %d was found!\n", x->key);
        RBT_delete(intTree, x); // Delete node from tree
    }

    RBT_export_dot(intTree);
    
    RBT_clear_tree(intTree);
    return 0;
}