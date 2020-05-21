#include "benchmarking/benchmark.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "benchmarking/avl_tree.h"
#include "benchmarking/binary_search_tree.h"
#include "benchmarking/colors.h"
#include "benchmarking/comparators.h"
#include "benchmarking/debug.h"
#include "benchmarking/red_black_tree.h"
#include "rbtree.h"

void shuffle(int* array, size_t n) {
    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void benchmark() {
    // benchmark_insert();
    benchmark_search();
}

void benchmark_search() {
    printf("\nSTART SEARCH BENCHMARKING\n");
    int iterations = 5;
    int elements_limit = 100000;
    FILE *pFile = fopen("search.csv", "w+");
    for(int elements = 1; elements <= elements_limit; elements = elements*2) {
        search(pFile, elements, iterations);
    }
    fclose(pFile);
}

void benchmark_insertion() {
    printf("\nSTART INSERT BENCHMARKING\n");
    int iterations = 10;
    int elements_limit = 100000;
    FILE *pFile = fopen("insertion.csv", "w+");
    for(int elements = 1; elements <= elements_limit; elements = elements*10) {
        unordered_insert(pFile, elements, iterations);
    }
    fclose(pFile);
}

void search(FILE *pFile, int count, int iterations) {
    int values[count];
    for (int i = 0; i < count; i++) {
        values[i] = i + 1;
    }
    shuffle(values, count);
    int last = count - 1;
    printf("elements %d\n", count);
    clock_t start;
    double total_time;
    double avg;

    // Search RBT
    RBT_t* rbTree = RBT_new_int();
    for (int i = 0; i < count; i++) {
        RBT_insert(rbTree, values[i], &values[i], sizeof(values[i]));
    }
    
    for(int i = 0; i < iterations; i++) {
        start = clock();
        RBT_search(rbTree, last);
        total_time += (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
    }
    avg = total_time / iterations;
    fprintf(pFile, "rbt,%d,%lf\n",count, avg);

    // Search RBT alternative (cstuff)
    binary_tree* rbt = new_binary_tree(compare_integer, ORD_ASC);
    for (int i = 0; i < count; i++) {
        int* data = malloc(sizeof(int));
        *data = values[i];
        node* n = tree_insert(rbt, data, FALSE);
    }

    for(int i = 0; i < iterations; i++) {
        start = clock();
        tree_search(rbt, (void *)&last);
        total_time += (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
    }
    avg = total_time / iterations;
    fprintf(pFile, "rbt2,%d,%lf\n",count, avg);

    // Search RBT alternative (cstuff)
    binary_tree* bst = new_binary_tree(compare_integer, ORD_ASC);
    for (int i = 0; i < count; i++) {
        int* data = malloc(sizeof(int));
        *data = values[i];
        node* n = tree_insert(bst, data, FALSE);
    }

    for(int i = 0; i < iterations; i++) {
        start = clock();
        tree_search(bst, (void *)&last);
        total_time += (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
    }
    avg = total_time / iterations;
    fprintf(pFile, "bst,%d,%lf\n",count, avg);
}

void unordered_insert(FILE *pFile, int count, int iterations) {
    int values[count];
    for (int i = 0; i < count; i++) {
        values[i] = i + 1;
    }
    shuffle(values, count);

    printf("\tInsertion of %d unordered integers\n", count);

    clock_t start;
    double total_time = 0;
    double avg;

    // Insert RBT
    for (int it = 1; it <= iterations; it++) {
        start = clock();
        RBT_t* rbTree = RBT_new_int();
        for (int i = 0; i < count; i++) {
            RBT_insert(rbTree, values[i], &values[i], sizeof(values[i]));
        }
        total_time += (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
        RBT_destroy(rbTree);
    }
    avg = total_time / (double)iterations;
    fprintf(pFile, "rbt,%d,%lf\n", count, avg);

    // Insert alternative RBT (cstuff)
    total_time = 0;
    for (int it = 1; it <= iterations; it++) {
        start = clock();
        binary_tree* rbt = new_binary_tree(compare_integer, ORD_ASC);
        for (int i = 0; i < count; i++) {
            int* data = malloc(sizeof(int));
            *data = values[i];
            rb_insert(rbt, (void*)data, FALSE);
        }

        total_time += (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
        delete_tree(rbt);
    }
    avg = total_time / (double)iterations;
    fprintf(pFile, "rbt2,%d,%lf\n",count, avg);

    // Insert BST
    total_time = 0;
    for (int it = 0; it <= iterations; it++) {
        start = clock();
        binary_tree* bst = new_binary_tree(compare_integer, ORD_ASC);
        for (int i = 0; i < count; i++) {
            int* data = malloc(sizeof(int));
            *data = values[i];
            node* n = tree_insert(bst, data, FALSE);
        }

        total_time += (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);

        delete_tree(bst);
    }
    avg = total_time / (double)iterations;
    fprintf(pFile, "bst,%d,%lf\n",count, avg);

    // Insert AVL
    total_time = 0;
    for (int it = 0; it <= iterations; it++) {
        start = clock();
        binary_tree* avl = new_binary_tree(compare_integer, ORD_ASC);
        for (int i = 0; i < count; i++) {
            int* data = malloc(sizeof(int));
            *data = values[i];
            node* n = tree_insert(avl, data, FALSE);
        }

        total_time += (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);

        delete_tree(avl);
    }
    avg = total_time / (double)iterations;
    fprintf(pFile, "avl,%d,%lf\n",count, avg);
}