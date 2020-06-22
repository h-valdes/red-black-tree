#include <stdio.h>
#include <stdlib.h>

#include "rbtree.h"
#include "benchmark.h"

int main(int argc, char* argv[]) {
    benchmark_insert("insert-ordered-1.csv", 20, 1, 100000, RBT_TRUE);
    benchmark_insert("insert-unordered-1.csv", 20, 1, 100000, RBT_FALSE);
    benchmark_search("search-1.csv", 20, 1, 100000);
    return 0;
}