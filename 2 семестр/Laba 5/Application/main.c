#include "kernel.h"

int sorting_method_number(int N) {
    return ((N - 1) % 15) + 1;
}

int table_structure_number(int N) {
    return ((N + 5) % 9) + 1;
}

void init(vector *values) {
    values->size = 0;
    values->capacity = 1;
    values->data = malloc(sizeof(int));
}

void increase_capacity(vector *values) {
    int *new_data = malloc(sizeof(int) * values->capacity * 2);
    for (int i = 0; i < values->size; i++) {
        new_data[i] = values->data[i];
    }
    free(values->data);
    values->data = new_data;
    values->capacity *= 2;
}

void push_back(vector *values, int val) {
    if (values->size == values->capacity) {
        increase_capacity(values);
    }
    values->data[values->size] = val;
    ++values->size;
}

void print(vector *values) {
    for (int i = 0; i < values->size; ++i) {
        printf("%d ", values->data[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shaker_sort(vector *values) {
    bool swapped = true;
    int start = 0;
    int end = values->size - 1;

    while (swapped) {
        swapped = false;

        // Проход слева направо
        for (int i = start; i < end; ++i) {
            if (values->data[i] > values->data[i + 1]) {
                swap(&values->data[i], &values->data[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;

        swapped = false;
        end--;

        // Проход справа налево
        for (int i = end - 1; i >= start; --i) {
            if (values->data[i] > values->data[i + 1]) {
                swap(&values->data[i], &values->data[i + 1]);
                swapped = true;
            }
        }

        start++;
    }
}

int bin_search(vector *values, int val) {
    int left = 0, right = values->size;
    while (right - left > 1) {
        int median = (right + left) / 2;
        if (values->data[median] > val) {
            right = median;
        } else {
            left = median;
        }
    }

    if (values->data[left] == val) {
        return left;
    }
    
    return -1;
}

int main() {
//    printf("Номер метода сортировки: %d\nНомер структуры таблицы: %d\n", sorting_method_number(4), table_structure_number(4));
    vector values;
    init(&values);

    for (int i = 0; i < 10; ++i) {
        int a;
        scanf("%d", &a);
        push_back(&values, a);
        // print(&values);
    }

    printf("\nИсходный вектор:\n");
    print(&values);

    shaker_sort(&values);

    printf("\nОтсортированный вектор:\n");
    print(&values);

    printf("%d\n", bin_search(&values, 10));
    printf("%d\n", bin_search(&values, 1));
    printf("%d\n", bin_search(&values, -10));
    printf("%d\n", bin_search(&values, 41234));
    printf("%d\n", bin_search(&values, 4));

}