#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

void print_int_data(void *data){
    printf("Data: %d\n", *(int *)data);
}

int main(int argc, char *argv[]){
    RBT_t *intTree = RBT_new(sizeof(int), &print_int_data);
    int value = 3;
    RBT_insert(intTree, 3, &value);

    value = 5;
    RBT_insert(intTree, 4, &value);

    value = 25;
    RBT_insert(intTree, 5, &value);

    value = 30;
    RBT_insert(intTree, 12, &value);

    RBT_delete(intTree, RBT_search(intTree, 3));

    RBT_insert(intTree, 7, &(int){15});
    RBT_insert(intTree, 6, &(int){15});

    RBT_print_data(intTree, RBT_search(intTree, 4));
    RBT_print_data(intTree, RBT_search(intTree, 5));
    RBT_print_data(intTree, RBT_search(intTree, 12));

    RBT_export_dot(intTree);
    
    RBT_clear_tree(intTree);
    return 0;
}