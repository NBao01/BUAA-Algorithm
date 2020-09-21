#include <stdio.h>
#include <stdlib.h>

void Merge(int Array[], int left, int mid, int right) {
    int *temp = (int *)malloc((right - left + 1) * sizeof(int));
    for (int i = left; i <= right; i++) {
        temp[i - left] = Array[i];
    }
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (temp[i - left] <= temp[j - left]) {
            Array[left + k] = temp[i - left];
            k++; i++;
        }
        else {
            Array[left + k] = temp[j - left];
            k++; j++;
        }
    }
    if (i <= mid) {
        while (i <= mid) {
            Array[left + k] = temp[i - left];
            k++; i++;
        }
    }
    else {
        while (j <= right) {
            Array[left + k] = temp[j - left];
            k++; j++;
        }
    }
}

void MergeSort(int Array[], int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = (left + right) / 2;
    MergeSort(Array, left, mid);
    MergeSort(Array, mid + 1, right);
    Merge(Array, left, mid, right);
}

int main() {
    int list[] = {9,4,6,8,2,5,7,1,3};
    char *s[2] = {"%d ", "%d\n"};
    for (int i = 0; i < 9; i++) {
        printf(s[i == 8], list[i]);
    }
    MergeSort(list, 0, 8);
    for (int i = 0; i < 9; i++) {
        printf(s[i == 8], list[i]);
    }
    return 0;
}
