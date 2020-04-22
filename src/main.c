#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    RBT_t *new_tree = RBT_new();
    RBT_delete(new_tree);
    return 0;
}