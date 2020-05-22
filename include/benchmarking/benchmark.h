#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdio.h>
#include <stdlib.h>
#include "benchmarking/avl_tree.h"
#include "benchmarking/binary_search_tree.h"
#include "benchmarking/colors.h"
#include "benchmarking/comparators.h"
#include "benchmarking/debug.h"
#include "benchmarking/red_black_tree.h"
#include "rbtree.h"

typedef enum __tree__t__{
    BST,
    RBT,
    AVL
}tree_t;

void benchmark_search();

void benchmark_insert();

void insert_cstuff(FILE *pFile,
                   tree_t tree_type, int values[],
                   int count, int iterations);

void insert_rbt(FILE *pFile, int values[], int count, int iterations);

void search_rbt(FILE *pFile, int values[], int count, int iterations);

void search_cstuff(FILE* pFile, tree_t tree_type,
                   int values[], int count, int iterations);

void shuffle(int *array, size_t n);

#endif