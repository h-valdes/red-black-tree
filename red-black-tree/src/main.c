#include <stdio.h>
#include <stdlib.h>

#include "rbtree.h"

int main(int argc, char* argv[]) {
    int count = 10;
    
    int values[count];
    printf("\n\tint RBT\n");

    // Generate a int RBT
    RBT_t *intTree = RBT_new_int();

    for (int i = 1; i < count + 1; i++) {
        values[i] = i;
        // Insert the node
        RBT_insert(intTree, i, &values[i], sizeof(values[i]));

        // Print the node
        RBT_print_node(intTree, i);

    }
    RBT_delete(intTree, RBT_search(intTree, 3));
    RBT_delete(intTree, RBT_search(intTree, 7));
    RBT_delete(intTree, RBT_search(intTree, 5));

    // Generate a DOT File of the tree
    RBT_export_dot(intTree, "intTree");

    RBT_destroy(intTree);

    printf("\n\tdouble RBT\n");

    double dValues[count];

    // Generate a double RBT
    RBT_t *doubleTree = RBT_new_double();

    for(int i = 1; i < count + 1; i++) {
        dValues[i] = ((double) i) / 10;
        // Insert the node
        RBT_insert(doubleTree, i, &dValues[i], sizeof(dValues[i])); 
        
        // Print the node
        RBT_print_node(doubleTree, i);
    }

    RBT_export_dot(doubleTree, "doubleTree");

    // Clear the trees
    RBT_destroy(doubleTree);

    return 0;
}