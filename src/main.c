#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    RBT_t *newTree = RBT_new();
    RBT_insert(newTree, 3);
    RBT_insert(newTree, 4);
    RBT_insert(newTree, 5);
    RBT_insert(newTree, 1);
    RBT_insert(newTree, 2);

    RBT_export_dot(newTree);
    
    RBT_clear_tree(newTree);
    return 0;
}