//
// Created by NBao on 2021/01/25.
//

#include <stdio.h>
#include <assert.h>

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

int Selection(int Array[], int begin, int end, int position) {
    int pivotPos = Partition(Array, begin, end);
    if (position == pivotPos - begin + 1) {
        return Array[pivotPos];
    }
    else if (position < pivotPos - begin + 1) {
        return Selection(Array, begin, pivotPos - 1, position);
    }
    else {
        return Selection(Array, pivotPos + 1, end, position - (pivotPos - begin + 1));
    }
}

int main() {
    int list[] = {-1, 9, 4, 6, 8, 2, 5, 7, 1, 3};

    printf("%d\n", Selection(list, 1, 9, 1));

    return 0;
}
