#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "benchmarking/binary_search_tree.h"
#include "benchmarking/comparators.h"
#include "benchmarking/debug.h"
#include "rbtree.h"

void visit(node* n)
{
      // printf("Visited node #%d\n",*(int*)n->data);
}

int main(int argc, char* argv[]) {
    int count = 10000;
    int values[count];
    for (int i = 1; i < count; i++) {
        values[i] = i;
    }

    // Insert RB Tree

    clock_t start = clock();
    
    RBT_t* intTree = RBT_new_int();
    for (int i = 1; i < count; i++) {
        RBT_insert(intTree, values[i], &values[i], sizeof(values[i]));
    }

    printf("Insertion Time RBT: %.6fms\n", (double)(clock() - start) / (CLOCKS_PER_SEC / 1000));

    RBT_clear_tree(intTree);

    // Insert BST

    start = clock();

    binary_tree* bt = new_binary_tree(compare_integer, ORD_ASC);    
    void* to_delete = NULL;
    node* suc = NULL;
    for (int i = 0; i < count; i++) {
        int* data = malloc(sizeof(int));
        *data = i;
        if (i == count - 1) to_delete = (void*)data;
        node* n = tree_insert(bt, data, TRUE);
        if (i == 3) suc = n;
    }
    printf("Insertion Time BST: %.6fms\n", (double)(clock() - start) / (CLOCKS_PER_SEC / 1000));
    
    depth_first(bt, visit, IN_ORDER);

    node* del = tree_delete(bt, to_delete);
    printf("Deleted node %d\n", *(int*)del->data);
    depth_first(bt, visit, IN_ORDER);

    return 0;
}