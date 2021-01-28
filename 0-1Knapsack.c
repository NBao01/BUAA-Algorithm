//
// Created by NBao on 2021/01/28.
//
// Input:
//     Set O contains n goods 1..n, v[i] is volume of good_i, p[i] is price of good_i
//     Capacity C
// Output:
//     \max{\sum_{i \in S} p[i]}, S \subset O
//

#include <stdio.h>
#define N 5
#define CAPACITY 13

int v[N + 1] = {-1, 10, 3, 4, 5, 4};
int p[N + 1] = {-1, 24, 2, 9, 10, 9};

int dp[N + 1][CAPACITY + 1];
int rec[N + 1][CAPACITY + 1];

int main() {
    for (int i = 0; i <= CAPACITY; i++) {
        dp[0][i] = 0;
    }
    for (int i = 0; i <= N; i++) {
        dp[i][0] = 0;
    }

    for (int i = 1; i <= N; i++) {
        for (int c = 1; c <= CAPACITY; c++) {
            if (v[i] <= c && p[i] + dp[i - 1][c - v[i]] > dp[i - 1][c]) {
                dp[i][c] =  p[i] + dp[i - 1][c - v[i]];
                rec[i][c] = 1;
            }
            else {
                dp[i][c] = dp[i - 1][c];
                rec[i][c] = 0;
            }
        }
    }

    int K = CAPACITY;
    for (int i = N; i >= 1; i--) {
        if (rec[i][K] == 1) {
            printf("Select Good_%d\n", i);
            K = K - v[i];
        }
        else {
            printf("Select Good_%d not\n", i);
        }
    }
    return 0;
}
