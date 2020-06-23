#include <stdio.h>
#include <stdlib.h>

#include "rbtree.h"
#include "benchmark.h"

int main(int argc, char* argv[]) {
    /*
     * BST worst case scenario is when it turns into a list, that happens
     * specially when the nodes are inserted in order. When the nodes are insert
     * randomly, the chances to become a list are minimal.
     * For AVL and RBT the average and worst case are the same, from a complexity
     * point of view at least. 
     */
    
    // Unorder insertion of nodes
    benchmark_insert("insert-avg.csv", 5, 1, 100000, RBT_FALSE);
    benchmark_search("search-avg.csv", 5, 1, 100000, RBT_FALSE);

    // In order insertion of nodes
    benchmark_insert("insert-worst.csv", 5, 1, 100000, RBT_TRUE);
    benchmark_search("search-worst.csv", 5, 1, 100000, RBT_TRUE);

    return 0;
}