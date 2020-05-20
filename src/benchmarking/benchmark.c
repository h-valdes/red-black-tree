#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "benchmarking/binary_search_tree.h"
#include "benchmarking/comparators.h"
#include "benchmarking/debug.h"
#include "rbtree.h"
#include "benchmarking/benchmark.h"

void visit(node* n) {
    // printf("Visited node #%d\n",*(int*)n->data);
}

void benchmark() {
    printf("\nSTART BENCHMARKING\n");
    int count = 1000;
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
        node* n = tree_insert(bt, data, TRUE);
    }
    printf("Insertion Time BST: %.6fms\n", (double)(clock() - start) / (CLOCKS_PER_SEC / 1000));

    depth_first(bt, visit, IN_ORDER);

}