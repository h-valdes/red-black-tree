#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    RBT_t *new_tree = RBT_new_tree();
    RBT_insert_node(new_tree, 3);
    RBT_insert_node(new_tree, 4);
    RBT_insert_node(new_tree, 1);
    RBT_insert_node(new_tree, 2);
    // RBT_print_node(new_tree->root_node);
    RBT_clear_tree(new_tree);
    return 0;
}