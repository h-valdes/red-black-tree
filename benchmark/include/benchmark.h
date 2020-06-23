#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"
#include "binary_search_tree.h"
#include "colors.h"
#include "comparators.h"
#include "debug.h"
#include "red_black_tree.h"
#include "rbtree.h"

typedef enum __tree__t__{
    BST,
    RBT,
    AVL
}tree_t;

void benchmark_search(char *filename,
                      int iterations, 
                      int start, 
                      int end, 
                      int in_order);

void benchmark_insert(char *filename,
                      int iterations, 
                      int start, 
                      int end, 
                      int in_order);

void insert_cstuff(FILE *pFile,
                   tree_t tree_type, 
                   int values[], 
                   int count, 
                   int iterations);

void insert_rbt(FILE *pFile, int values[], int count, int iterations);

void search_rbt(FILE *pFile, int values[], int count, int iterations);

void search_cstuff(FILE *pFile,
                   tree_t tree_type,
                   int values[], 
                   int count, 
                   int iterations);

void shuffle(int *array, size_t n);

#endif