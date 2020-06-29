#include "benchmark.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "avl_tree.h"
#include "binary_search_tree.h"
#include "colors.h"
#include "comparators.h"
#include "debug.h"
#include "red_black_tree.h"
#include "rbtree.h"

/*
 * Implementation from StackOverflow user John Leehey 
 * https://stackoverflow.com/questions/6127503/shuffle-array-in-c
 */
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
                    tree_insert(bt, (void*)data, FALSE);
                    break;
                case (RBT):
                    strcpy(name, "RBT2");
                    rb_insert(bt, (void*)data, FALSE);
                    break;
                case (AVL):
                    strcpy(name, "AVL");
                    avl_insert(bt, (void*)data, FALSE);
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
                tree_insert(bt, (void*)data, FALSE);
                break;
            case (RBT):
                strcpy(name, "RBT2");
                rb_insert(bt, (void*)data, FALSE);
                break;
            case (AVL):
                strcpy(name, "AVL");
                avl_insert(bt, (void*)data, FALSE);
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

void benchmark_search(char* filename,
                      int iterations, 
                      int start, 
                      int end, 
                      int in_order) {
    printf("\nSTART SEARCH BENCHMARKING\n");
    int parts = (end > 100) ? 100 : end;
    int jump = (int)round((double)(end - start) / parts);
    FILE* pFile = fopen(filename, "w+");

    for (int i = 0; i < 4; i++) {
        for (int count = start; count <= end + 1; count += jump) {
            printf("\tSearch on tree with %d elements\n", count);
            if (count > end) {
                count = end;
            }
            int values[count];
            for (int i = 0; i < count; i++) {
                values[i] = i;
            }
            if (in_order == RBT_FALSE) {
                shuffle(values, count);
            }

            switch(i) {
                case 0:
                    search_rbt(pFile, values, count, iterations);
                    break;
                case 1:
                    search_cstuff(pFile, RBT, values, count, iterations);
                    break;
                case 2:
                    search_cstuff(pFile, AVL, values, count, iterations);
                    break;
                case 3:
                    search_cstuff(pFile, BST, values, count, iterations);
                    break;
            }            
            if (count == end) {
                break;
            }
        }
    }

    fclose(pFile);
}

void benchmark_insert(char* filename,
                      int iterations, 
                      int start, 
                      int end, 
                      int in_order) {
    printf("\nSTART INSERT BENCHMARKING\n");
    int parts = (end > 100) ? 100 : end;
    int jump = (int)round((double)(end - start) / parts);
    FILE* pFile = fopen(filename, "w+");
    
    for (int i = 0; i < 4; i++) {
        for (int count = start; count <= end + 1; count += jump) {
            if (count > end) {
                count = end;
            }
            int values[count];
            for (int i = 0; i < count; i++) {
                values[i] = i;
            }
            if (in_order == RBT_FALSE) {
                shuffle(values, count);
            }

            printf("\tInsertion of %d unordered integers\n", count);

            switch(i) {
                case 0:
                    insert_rbt(pFile, values, count, iterations);
                    break;
                case 1:
                    insert_cstuff(pFile, RBT, values, count, iterations);
                    break;
                case 2:
                    insert_cstuff(pFile, AVL, values, count, iterations);
                    break;
                case 3:
                    insert_cstuff(pFile, BST, values, count, iterations);
                    break;
            }

            if (count == end) {
                break;
            }
        }
    }
    fclose(pFile);
}
