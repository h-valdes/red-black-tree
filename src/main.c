#include <stdio.h>
#include <stdlib.h>

#include "rbtree.h"
#include "benchmarking/benchmark.h"

int main(int argc, char* argv[]) {
    int count = 100000;
    
    int values[count];
    printf("\n\tint RBT\n");

    // Generate a int RBT
    RBT_t *intTree = RBT_new_int();

    for (int i = 1; i < count + 1; i++) {
        values[i] = i;
        // Insert the node
        RBT_insert(intTree, i, &values[i], sizeof(values[i]));
    }

    // Print the node
    RBT_print_node(intTree, 95130);

    RBT_destroy(intTree);

    // Generate a DOT File of the tree
    RBT_export_dot(intTree, "intTree");

    printf("\n\tdouble RBT\n");

    double dValues[count];

    // Generate a double RBT
    RBT_t *doubleTree = RBT_new_double();

    for(int i = 1; i < count + 1; i++) {
        dValues[i] = ((double) i) / 100;
        // Insert the node
        RBT_insert(doubleTree, i, &dValues[i], sizeof(dValues[i])); 
        
        // Print the node
        RBT_print_node(doubleTree, i);
    }

    RBT_export_dot(doubleTree, "doubleTree");

    // Clear the trees
    RBT_destroy(intTree);
    RBT_destroy(doubleTree);

    // benchmark();

    return 0;
}