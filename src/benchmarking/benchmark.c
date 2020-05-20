#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "benchmarking/binary_search_tree.h"
#include "benchmarking/red_black_tree.h"
#include "benchmarking/colors.h"
#include "benchmarking/comparators.h"
#include "benchmarking/debug.h"
#include "benchmarking/benchmark.h"

#include "rbtree.h"

void visit_bst(node* n) {
    // printf("Visited node #%d\n",*(int*)n->data);
}

void visit_rbt(node* n)
{
    DBG("Visited node #%d (%c) \tPARENT=%d (%c)\tHEIGHT=%d, COLOR=%d\n",
    *(int*)n->data,
    *(int*)n->data,
    n->parent?*(int*)n->parent->data:-1,
    n->parent?*(int*)n->parent->data:'*',
    height(n),
    n->color
    );
}

void benchmark() {
    printf("\nSTART BENCHMARKING\n");

    // Generate 10000 elements in order and
    int count = 10000;
    int values[count];
    for (int i = 1; i < count; i++) {
        values[i] = i;
    }

    printf("\tInsertion of %d ordered/ascendent integers\n", count);

    // Insert RB Tree

    clock_t start = clock();

    RBT_t* rbTree = RBT_new_int();
    for (int i = 1; i < count; i++) {
        RBT_insert(rbTree, values[i], &values[i], sizeof(values[i]));
    }

    printf("\tInsertion Time RBT: %.6fms\n", (double)(clock() - start) / (CLOCKS_PER_SEC / 1000));

    RBT_clear_tree(rbTree);

    // Insert alternative RBT (cstuff)
    start = clock();

    binary_tree* rbt = new_binary_tree(compare_integer, ORD_ASC);
    for (int i = 1; i < count; i++) {
        int* data = malloc(sizeof(int));
        *data = values[i];
        rb_insert(rbt, (void*)data, TRUE);
    }

    printf("\tInsertion Time RBT (cstuff library): %.6fms\n", (double)(clock() - start) / (CLOCKS_PER_SEC / 1000));

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
    printf("\tInsertion Time BST (cstuff library): %.6fms\n", (double)(clock() - start) / (CLOCKS_PER_SEC / 1000));

    

    

}