//
// Created by NBao on 2021/01/29.
//
// Input:
//     Set O contains n goods 1..n, v[i] is volume of good_i, p[i] is price of good_i
//     Capacity C
// Output:
//     Solution S = {x_i | 1 <= i <= n, 0 <= x_i <= 1},
//     let max \sum_{x_i \in S} (x_i * p_i), s.t. \sum_{x_i \in S} (x_i * v*i) <= C.
//

#include <stdio.h>
#define N 5
#define CAPACITY 800

void swap(double *a, double *b);
int Partition(int begin, int end);
void Quicksort(int begin, int end);

int v[N + 1] = {-1, 600, 250, 200, 100, 300};
int p[N + 1] = {-1, 60, 10, 36, 16, 45};
double ratio[N + 1];

int main() {
    for (int i = 1; i <= N; i++) {
        ratio[i] = (1.0 * p[i]) / v[i];
    }
    Quicksort(1, 5);    // DESC ORDER

    printf("-------------------------------------------------\n");
    printf("|\tvolume\t|\tprice\t|\tratio\t|\n");
    printf("-------------------------------------------------\n");
    for (int i = 1; i <= N; i++) {
        printf("|\t%d\t|\t%d\t|\t%.2lf\t|\n", v[i], p[i], ratio[i]);
    }
    printf("-------------------------------------------------\n");

    int i = 1;
    double ans = 0;
    int C = CAPACITY;
    while (C > 0 && i <= N) {
        if (v[i] <= C) {
            printf("Select All Good_%d\n", i);
            ans += p[i];
            C -= v[i];
        }
        else {
            printf("Select Good_%d of volume %d\n", i, C);
            ans += p[i] * (1.0 * C) / v[i];
            C = 0;
        }
        i++;
    }
    printf("The max price is %.2lf\n", ans);
}

void swap_int(int *a, int *b) {
    int temp;
    temp = *b;
    *b = *a;
    *a = temp;
}

void swap(double *a, double *b) {
    double temp;
    temp = *b;
    *b = *a;
    *a = temp;
}

int Partition(int begin, int end) {
    double pivot = ratio[end];
    int i = begin;
    for (int j = begin; j < end; j++) {
        if (ratio[j] >= pivot) {
            swap(&ratio[j], &ratio[i]);
            swap_int(&v[j], &v[i]);
            swap_int(&p[j], &p[i]);
            i++;
        }
    }
    swap(&ratio[i], &ratio[end]);
    swap_int(&v[i], &v[end]);
    swap_int(&p[i], &p[end]);
    return i;
}

void Quicksort(int begin, int end) {
    if (begin < end) {
        int pivotPos = Partition(begin, end);
        Quicksort(begin, pivotPos - 1);
        Quicksort(pivotPos + 1, end);
    }
}