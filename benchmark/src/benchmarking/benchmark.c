#include "benchmarking/benchmark.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void insert_cstuff(FILE* pFile, tree_t tree_type,
                   int values[], int count, int iterations) {
    time_t start;
    double total_time = 0;
    double worst = 0;
    double avg = 0;
    char name[5];

    for (int it = 1; it <= iterations; it++) {
        binary_tree* bt = new_binary_tree(compare_integer, ORD_ASC);
        start = clock();
        for (int i = 0; i < count; i++) {
            int* data = malloc(sizeof(int));
            *data = values[i];
            switch (tree_type) {
                case (BST):
                    strcpy(name, "BST");
                    tree_insert(bt, (void*)data, TRUE);
                    break;
                case (RBT):
                    strcpy(name, "RBT2");
                    rb_insert(bt, (void*)data, TRUE);
                    break;
                case (AVL):
                    strcpy(name, "AVL");
                    avl_insert(bt, (void*)data, TRUE);
                    break;
            }
        }

        double time = (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
        total_time += time;
        if (time > worst) {
            worst = time;
        }
        delete_tree(bt);
    }
    avg = total_time / (double)iterations;
    fprintf(pFile, "%s,%d,%lf,%lf\n", name, count, avg, worst);
}

void insert_rbt(FILE* pFile, int values[], int count, int iterations) {
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
        if (time > worst) {
            worst = time;
        }
        RBT_destroy(rbTree);
    }
    avg = total_time / (double)iterations;
    fprintf(pFile, "RBT,%d,%lf,%lf\n", count, avg, worst);
}

void search_rbt(FILE *pFile, int values[], int count, int iterations) {
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

    for (int i = 0; i < iterations; i++) {
        start = clock();
        RBT_search(rbTree, last);
        double time = (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
        total_time += time;
        if (time > worst) {
            worst = time;
        }
    }
    avg = total_time / iterations;
    fprintf(pFile, "RBT,%d,%lf,%lf\n", count, avg, worst);
    RBT_destroy(rbTree);
}

void search_cstuff(FILE* pFile, tree_t tree_type,
                   int values[], int count, int iterations) {
    time_t start;
    double total_time = 0;
    double avg = 0;
    double worst = 0;
    char name[5];
    int last = count - 1;

    binary_tree* bt = new_binary_tree(compare_integer, ORD_ASC);
    for (int i = 0; i < count; i++) {
        int* data = malloc(sizeof(int));
        *data = values[i];
        switch (tree_type) {
            case (BST):
                strcpy(name, "BST");
                tree_insert(bt, (void*)data, TRUE);
                break;
            case (RBT):
                strcpy(name, "RBT2");
                rb_insert(bt, (void*)data, TRUE);
                break;
            case (AVL):
                strcpy(name, "AVL");
                avl_insert(bt, (void*)data, TRUE);
                break;
        }
    }

    for (int i = 0; i < iterations; i++) {
        start = clock();
        tree_search(bt, (void*)&last);
        double time = (double)(clock() - start) / (CLOCKS_PER_SEC / 1000);
        total_time += time;
        if (time > worst) {
            worst = time;
        }
    }

    delete_tree(bt);
    avg = total_time / iterations;
    fprintf(pFile, "%s,%d,%lf,%lf\n", name, count, avg, worst);
}

void benchmark_search() {
    printf("\nSTART SEARCH BENCHMARKING\n");
    int iterations = 20;
    int start = 1;
    int end = 100000;
    int parts = 100;
    int jump = (int)round((double)(end - start) / parts);
    char filename[50];
    sprintf(filename, "search-%d-%d.csv", start, end);
    FILE* pFile = fopen(filename, "w+");
    for (int count = start; count <= end + 1; count += jump) {
        printf("\tSearch on tree with %d elements\n", count);
        int values[count];
        for (int i = 0; i < count; i++) {
            values[i] = i;
        }
        // shuffle(values, count);

        // Search BST alternative (cstuff)
        search_cstuff(pFile, BST, values, count, iterations);

        // Search AVL alternative (cstuff)
        search_cstuff(pFile, AVL, values, count, iterations);

        // Search RBT alternative (cstuff)
        search_cstuff(pFile, RBT, values, count, iterations);

        search_rbt(pFile, values, count, iterations);
    }
    fclose(pFile);
}

void benchmark_insert() {
    printf("\nSTART INSERT BENCHMARKING\n");
    int iterations = 20;
    int start = 1;
    int end = 100000;
    int parts = 100;
    int jump = (int)round((double)(end - start) / parts);
    char filename[50];
    sprintf(filename, "insert-%d-%d.csv", start, end);
    FILE* pFile = fopen(filename, "w+");
    for (int count = start; count <= end + 1; count += jump) {
        int values[count];
        for (int i = 0; i < count; i++) {
            values[i] = i;
        }
        shuffle(values, count);

        printf("\tInsertion of %d unordered integers\n", count);

        insert_rbt(pFile, values, count, iterations);

        // Insert alternative RBT (cstuff)
        insert_cstuff(pFile, RBT, values, count, iterations);

        // Insert BST
        insert_cstuff(pFile, BST, values, count, iterations);

        // Insert AVL
        insert_cstuff(pFile, AVL, values, count, iterations);
    }
    fclose(pFile);
}
