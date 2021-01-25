//
// Created by NBao on 2021/01/25.
//
// Input: An array of reals A[1..n]
// Output: The total number of inversions, namely \sum_{1<=i<j<=n} X_{i,j}
//
// X_{i,j} = {
//     1,    A[i] > A[j]
//     0,    A[i] <= A[j]
// }
//

#include <stdio.h>
#include <stdlib.h>

int MergeAndCount(int Array[], int left, int mid, int right) {
    int count = 0;

    // Move Array[left..right] to temp[]
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
            count += mid - i + 1;   // Increase count by left part's remain length
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
    return count;
}

int MergeSort(int Array[], int left, int right) {
    if (left >= right) {
        return 0;
    }
    int count = 0;
    int mid = (left + right) / 2;
    count += MergeSort(Array, left, mid);
    count += MergeSort(Array, mid + 1, right);
    count += MergeAndCount(Array, left, mid, right);
    return count;
}

int main() {
    int list[] = {9, 4, 6, 8, 2, 5, 7, 1, 3};
    char *s[2] = {"%d ", "%d\n"};
    for (int i = 0; i < 9; i++) {
        printf(s[i == 8], list[i]);
    }
    int count = MergeSort(list, 0, 8);
    printf("Inversion numbers is %d\n", count);
    for (int i = 0; i < 9; i++) {
        printf(s[i == 8], list[i]);
    }
    return 0;
}


