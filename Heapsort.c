//
// Created by NBao on 2021/01/28.
//

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp;
    temp = *b;
    *b = *a;
    *a = temp;
}

void BuildHeap(int heap[], const int list[], int length) {
    for (int i = 0; i < length; i++) {
        heap[i] = list[i];
        int j = i;
        while (j > 0 && heap[j] < heap[(j - 1) / 2]) {
            swap(&heap[j], &heap[(j - 1) / 2]);
            j = (j - 1) / 2;
        }
    }
}

int ExtractMin(int heap[], int* heapLength) {
    int ret = heap[0];

    // Restore min-heap
    heap[0] = heap[--(*heapLength)];
    int j = 0;
    while ((2 * j + 2) < (*heapLength)) {
        if (heap[2 * j + 1] <= heap[2 * j + 2]) {
            if (heap[j] > heap[2 * j + 1]) {
                swap(&heap[j], &heap[2 * j + 1]);
                j = 2 * j + 1;
            }
            else break;
        }
        else {
            if (heap[j] > heap[2 * j + 2]) {
                swap(&heap[j], &heap[2 * j + 2]);
                j = 2 * j + 2;
            }
            else break;
        }
    }

    // If there is only one child for the last j out from loop
    if ((2 * j + 1) < (*heapLength) && heap[j] > heap[2 * j + 1]) {
        swap(&heap[j], &heap[2 * j + 1]);
    }

    return ret;
}

void Heapsort(int list[], int length) {
    int *heap = (int *)malloc(length * sizeof(int));
    BuildHeap(heap, list, length);
    int heapLength = length;
    for (int i = 0; i < length; i++) {
        list[i] = ExtractMin(heap, &heapLength);
    }
}

void OutputList(int list[], int length) {
    char *s[2] = {"%d ", "%d\n"};

    for (int i = 0; i < length; i++) {
        printf(s[i == (length - 1)], list[i]);
    }
}

int main() {
    int list[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    OutputList(list, 10);
    Heapsort(list, 10);
    OutputList(list, 10);
    return 0;
}