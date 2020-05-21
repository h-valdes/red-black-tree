#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdlib.h>
#include <stdio.h>

void unordered_insert(FILE *pFile, int count, int iterations);

void search(FILE *pFile, int count, int iterations);

void benchmark();

void benchmark_search();

void benchmark_insert();

void shuffle(int* array, size_t n);

#endif