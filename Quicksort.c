//
// Created by NBao on 2021/01/25.
//

#include <stdio.h>

void swap(int *a, int *b) {
    int temp;
    temp = *b;
    *b = *a;
    *a = temp;
}

int Partition(int Array[], int begin, int end) {
    int pivot = Array[end];
    int i = begin;
    for (int j = begin; j < end; j++) {
        if (Array[j] <= pivot) {
            swap(&Array[j], &Array[i++]);
        }
    }
    swap(&Array[i], &Array[end]);
    return i;
}

void Quicksort(int Array[], int begin, int end) {
    if (begin < end) {
        int pivotPos = Partition(Array, begin, end);
        Quicksort(Array, begin, pivotPos - 1);
        Quicksort(Array, pivotPos + 1, end);
    }
}

int main() {
    int list[] = {9, 4, 6, 8, 2, 5, 7, 1, 3};
    char *s[2] = {"%d ", "%d\n"};

    for (int i = 0; i < 9; i++) {
        printf(s[i == 8], list[i]);
    }
    Quicksort(list, 0, 8);
    for (int i = 0; i < 9; i++) {
        printf(s[i == 8], list[i]);
    }

    return 0;
}