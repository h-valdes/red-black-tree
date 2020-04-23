#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    RBT_t *new_tree = RBT_new_tree();
    RBT_insert_node(new_tree, 1);
    printf("Root key: %d\n", new_tree->root_node->key);
    RBT_clear_tree(new_tree);
    return 0;
}