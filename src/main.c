#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    RBT_t *intTree = RBT_new_int();
    int value = 3;
    RBT_insert(intTree, 3, &value, sizeof(value));

    value = 5;
    RBT_insert(intTree, 4, &value, sizeof(value));

    value = 25;
    RBT_insert(intTree, 5, &value, sizeof(value));

    value = 30;
    RBT_insert(intTree, 12, &value, sizeof(value));

    RBT_delete(intTree, RBT_search(intTree, 3));

    RBT_print_node(intTree, 4);
    RBT_print_node(intTree, 5);
    RBT_print_node(intTree, 12);

    RBT_export_dot(intTree);
    
    RBT_clear_tree(intTree);

    RBT_t *strTree = RBT_new_str();
    char text[] = "hola";
    RBT_insert(strTree, 1, &text, sizeof(text));

    char new_text[] = "new super text, extra loooong!";
    RBT_insert(strTree, 2, &new_text, sizeof(new_text));

    RBT_print_node(strTree, 1);
    RBT_print_node(strTree, 2);

    RBT_clear_tree(strTree);

    return 0;
}