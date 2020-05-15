#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

void print_int_data(void *data){
    printf("Printing %d\n", *(int *)data);
}

int main(int argc, char *argv[]){
    RBT_t *intTree = RBT_new(&print_int_data);
    RBT_insert(intTree, 3, &(int){10});
    RBT_insert(intTree, 4, &(int){15});
    RBT_insert(intTree, 5, &(int){25});
    RBT_insert(intTree, 12, &(int){15});

    RBT_delete(intTree, RBT_search(intTree, 3));
    // Node_t *y = RBT_search(intTree, 4); // Search a node

    RBT_insert(intTree, 7, &(int){15});
    RBT_insert(intTree, 6, &(int){15});
    RBT_export_dot(intTree);
    
    RBT_clear_tree(intTree);
    return 0;
}