#ifndef SORT_H
#define SORT_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

int sorting_method_number(int N);
int table_structure_number(int N);

typedef struct {
    int size;
    int capacity;
    int* data;  // Статический массив (указатель на начало)
} vector;

void push_back(vector *values, int val);
void increase_capacity(vector *values);
void init(vector *values);
void print(vector *values);
void swap(int *a, int *b);
void shaker_sort(vector *values);
int bin_search(vector *values, int val);

#endif