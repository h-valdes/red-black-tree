#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdlib.h>
#include <stdio.h>

void ordered_insertion(int count, int iterations);

void unordered_insertion(FILE *pFile, int count, int iterations);

void search();

void benchmark();

void shuffle(int* array, size_t n);

#endif