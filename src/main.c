#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rbtree.h"
#include "benchmarking/benchmark.h"

int main(int argc, char* argv[]) {
    int count = 10;
    int values[count];
    for (int i = 1; i < count; i++) {
        values[i] = i;
    }

    RBT_t* intTree = RBT_new_int();
    for (int i = 1; i < count; i++) {
        RBT_insert(intTree, values[i], &values[i], sizeof(values[i]));
    }

    RBT_clear_tree(intTree);

    benchmark();

    return 0;
}