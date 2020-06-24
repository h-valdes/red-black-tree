#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "rbtree.h"

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB_t;

void print_color(Node_t *pNode) {
    printf(
        "Node: %d || RGB: (%d, %d, %d)\n", 
        pNode->key,  
        ((RGB_t *)(pNode->data))->r,
        ((RGB_t *)(pNode->data))->g,
        ((RGB_t *)(pNode->data))->b);
}

int main(int argc, char* argv[]) {
    // Create a custom RBT with custom data (ex: RGB_t struct)
    printf("rgb RBT\n");
    RBT_t *rgbTree = RBT_new(print_color);
    RGB_t new_color = {.r=200, .g=100, .b=230};
    RBT_insert(rgbTree, 1, &new_color, sizeof(new_color));
    RBT_print_node(rgbTree, 1);
    RBT_destroy(rgbTree);

    // Generate a int RBT
    printf("\n\tint RBT\n");  
    int count = 10;
    int values[count];

    RBT_t *intTree = RBT_new_int();

    for (int i = 1; i < count + 1; i++) {
        values[i] = i;
        // Insert the node
        RBT_insert(intTree, i, &values[i], sizeof(values[i]));

        // Print the node
        RBT_print_node(intTree, i);

    }
    
    RBT_delete(intTree, 3);
    RBT_delete(intTree, 7);
    RBT_delete(intTree, 5);

    // Generate a DOT File of the tree
    RBT_export_dot(intTree, "intTree", RBT_FALSE);

    int new_value = 20;
    RBT_insert(intTree, 15, &new_value, sizeof(new_value));
    RBT_print_node(intTree, 15);

    RBT_export_dot(intTree, "intTreePres1", RBT_TRUE);
    RBT_export_dot(intTree, "intTreePres2", RBT_FALSE);

    RBT_destroy(intTree);

    // Generate a double RBT
    printf("\n\tdouble RBT\n");
    double dValues[count];
    RBT_t *doubleTree = RBT_new_double();

    for(int i = 1; i < count + 1; i++) {
        dValues[i] = ((double) i) / 10;
        // Insert the node
        RBT_insert(doubleTree, i, &dValues[i], sizeof(dValues[i])); 
        
        // Print the node
        RBT_print_node(doubleTree, i);
    }

    RBT_export_dot(doubleTree, "doubleTree", RBT_TRUE);

    // Clear the trees
    RBT_destroy(doubleTree);

    return 0;
}