//
// Created by NBao on 2021/01/28.
//
// Input: An array of reals A[1..n]
// The value of subarray A[i..j] is V(i, j) = \sum_{x=i}^{j} A(x)
// Find i <= j such that V(i, j) is maximized
//

#include <stdio.h>

#define N 9

int list[N] = {-3, 2, 1, -4, 5, 2, -1, 3, -1};
int dp[N];
int rec[N];

int main() {
    dp[N - 1] = list[N - 1];
    rec[N - 1] = N - 1;

    for (int i = N - 2; i >= 0; i--) {
        if (dp[i + 1] > 0) {
            dp[i] = dp[i + 1] + list[i];
            rec[i] = rec[i + 1];
        }
        else {
            dp[i] = list[i];
            rec[i] = i;
        }
    }

    int V = dp[0];
    int l = 0, r = rec[0];
    for (int i = 1; i < N; i++) {
        if (V < dp[i]) {
            V = dp[i];
            l = i;
            r = rec[i];
        }
    }
    printf("The Maximum Contiguous Subarray is from %d to %d\n"
           "The max value is %d\n", l, r, V);
    return 0;
}

