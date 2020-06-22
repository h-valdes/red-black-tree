#include <stdio.h>
#include <stdlib.h>

#include "rbtree.h"
#include "benchmark.h"

int main(int argc, char* argv[]) {
    benchmark_insert(RBT_TRUE);
    benchmark_insert(RBT_FALSE);
    benchmark_search();
    return 0;
}