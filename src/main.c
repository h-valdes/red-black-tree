#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    RBT_t *new_tree = RBT_new_tree();
    RBT_clear_tree(new_tree);
    return 0;
}