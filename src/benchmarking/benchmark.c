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
    benchmark_insert();
    benchmark_search();
}


void benchmark_search() {
    printf("\nSTART SEARCH BENCHMARKING\n");
    int iterations = 10;
    int elements_limit = 100000;
    int jump = (int) round((double)elements_limit / 100);
    FILE *pFile = fopen("search.csv", "w+");
    for(int elements = 1; elements <= elements_limit; elements += jump) {
        search(pFile, elements, iterations);
    }
    fclose(pFile);
}

void benchmark_insert() {
    printf("\nSTART INSERT BENCHMARKING\n");
    int iterations = 10;
    int elements_limit = 100000;
    int jump = (int) round((double)elements_limit / 100);
    FILE *pFile = fopen("insert.csv", "w+");
    for(int elements = 0; elements <= elements_limit; elements += jump) {
        unordered_insert(pFile, elements+1, iterations);
    }
    fclose(pFile);
}

void search(FILE *pFile, int count, int iterations) {
    printf("\tSearch on tree with %d elements\n", count);
    int values[count];
    for (int i = 0; i < count; i++) {
        values[i] = i + 1;
    }
    // shuffle(values, count);
    int last = count - 1;
    printf("elements %d\n", count);
    clock_t start;
    double total_time;
    double avg;
    double worst = 0;

    // Search RBT
    total_time = 0;
    avg = 0;
    worst = 0;
    RBT_t* rbTree = RBT_new_int();
    for (int i = 0; i < count; i++) {
        RBT_insert(rbTree, values[i], &values[i], sizeof(values[i]));
    }
    
    for(int i = 0; i < iterations; i++) {
        start = clock();
        RBT_search(rbTree, last);
        double time = (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
        total_time += time;
        if(time > worst) {
            worst = time;
        } 
    }
    avg = total_time / iterations;
    fprintf(pFile, "RBT,%d,%lf,%lf\n",count, avg, worst);
    RBT_destroy(rbTree);

    // Search RBT alternative (cstuff)
    total_time = 0;
    avg = 0;
    worst = 0;
    binary_tree* rbt = new_binary_tree(compare_integer, ORD_ASC);
    for (int i = 0; i < count; i++) {
        int* data = malloc(sizeof(int));
        *data = values[i];
        node* n = rb_insert(rbt, data, TRUE);
    }

    for(int i = 0; i < iterations; i++) {
        start = clock();
        tree_search(rbt, (void *)&last);
        double time = (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
        total_time += time;
        if(time > worst) {
            worst = time;
        } 
    }
    avg = total_time / iterations;
    fprintf(pFile, "RBT2,%d,%lf,%lf\n",count, avg, worst);

    // Search BST alternative (cstuff)
    total_time = 0;
    avg = 0;
    worst = 0;
    binary_tree* bst = new_binary_tree(compare_integer, ORD_ASC);
    for (int i = 0; i < count; i++) {
        int* data = malloc(sizeof(int));
        *data = values[i];
        node* n = tree_insert(bst, data, TRUE);
    }

    for(int i = 0; i < iterations; i++) {
        start = clock();
        tree_search(bst, (void *)&last);
        double time = (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
        total_time += time;
        if(time > worst) {
            worst = time;
        } 
    }
    avg = total_time / iterations;
    fprintf(pFile, "BST,%d,%lf,%lf\n",count, avg, worst);

    // Search AVL alternative (cstuff)
    total_time = 0;
    avg = 0;
    worst = 0;
    binary_tree* avl = new_binary_tree(compare_integer, ORD_ASC);
    for (int i = 0; i < count; i++) {
        int* data = malloc(sizeof(int));
        *data = values[i];
        node* n = avl_insert(avl, data, TRUE);
    }

    for(int i = 0; i < iterations; i++) {
        start = clock();
        tree_search(avl, (void *)&last);
        double time = (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
        total_time += time;
        if(time > worst) {
            worst = time;
        } 
    }
    avg = total_time / iterations;
    fprintf(pFile, "AVL,%d,%lf,%lf\n",count, avg, worst);
}

void unordered_insert(FILE *pFile, int count, int iterations) {
    int values[count];
    for (int i = 0; i < count; i++) {
        values[i] = i + 1;
    }
    // shuffle(values, count);

    printf("\tInsertion of %d unordered integers\n", count);

    clock_t start;
    double total_time = 0;
    double avg;
    double worst = 0;

    // Insert RBT
    for (int it = 1; it <= iterations; it++) {
        start = clock();
        RBT_t* rbTree = RBT_new_int();
        for (int i = 0; i < count; i++) {
            RBT_insert(rbTree, values[i], &values[i], sizeof(values[i]));
        }
        double time = (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
        total_time += time;
        if(time > worst) {
            worst = time;
        } 
        RBT_destroy(rbTree);
    }
    avg = total_time / (double)iterations;
    fprintf(pFile, "RBT,%d,%lf,%lf\n", count, avg, worst);

    // Insert alternative RBT (cstuff)
    total_time = 0;
    worst = 0;
    for (int it = 1; it <= iterations; it++) {
        start = clock();
        binary_tree* rbt = new_binary_tree(compare_integer, ORD_ASC);
        for (int i = 0; i < count; i++) {
            int* data = malloc(sizeof(int));
            *data = values[i];
            rb_insert(rbt, (void*)data, FALSE);
        }

        double time = (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
        total_time += time;
        if(time > worst) {
            worst = time;
        } 
        delete_tree(rbt);
    }
    avg = total_time / (double)iterations;
    fprintf(pFile, "RBT2,%d,%lf,%lf\n",count, avg, worst);

    // Insert BST
    total_time = 0;
    worst = 0;
    for (int it = 0; it <= iterations; it++) {
        start = clock();
        binary_tree* bst = new_binary_tree(compare_integer, ORD_ASC);
        for (int i = 0; i < count; i++) {
            int* data = malloc(sizeof(int));
            *data = values[i];
            node* n = tree_insert(bst, data, FALSE);
        }

        double time = (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
        total_time += time;
        if(time > worst) {
            worst = time;
        } 

        delete_tree(bst);
    }
    avg = total_time / (double)iterations;
    fprintf(pFile, "BST,%d,%lf,%lf\n",count, avg, worst);

    // Insert AVL
    total_time = 0;
    worst = 0;
    for (int it = 0; it <= iterations; it++) {
        start = clock();
        binary_tree* avl = new_binary_tree(compare_integer, ORD_ASC);
        for (int i = 0; i < count; i++) {
            int* data = malloc(sizeof(int));
            *data = values[i];
            node* n = avl_insert(avl, data, FALSE);
        }

        double time = (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
        total_time += time;
        if(time > worst) {
            worst = time;
        } 

        delete_tree(avl);
    }
    avg = total_time / (double)iterations;
    fprintf(pFile, "AVL,%d,%lf,%lf\n",count, avg, worst);
}