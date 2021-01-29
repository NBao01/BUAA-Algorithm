//
// Created by NBao on 2021/01/29.
//
// Input:
//     The length of Rod is n
//     The price list p_l (1 <= l <= n): represent the price of l length rod
// Output:
//     Solve a set of cutting plans T = <c_1, c_2, ..., c_m>
//     let max \sum_{l=1}^m{p_{c_l}}
//     s.t. \sum_{l=1}^m{c_l} = m
//

#include <stdio.h>

#define N 10

int p[N + 1] = {-1, 1, 5, 8, 9, 10, 17, 17, 20, 24, 24};
int dp[N + 1];
int rec[N + 1];

int main() {
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
        int price = p[i];
        rec[i] = i;
        for (int j = 1; j <= i - 1; j++) {
            if (price < p[j] + dp[i - j]) {
                price = p[j] + dp[i - j];
                rec[i] = j;
            }
        }
        dp[i] = price;
    }

    int n = N;
    while (n > 0) {
        printf("%d", rec[n]);
        n = n - rec[n];
        if (n > 0) {
            printf(", ");
        }
        else {
            printf("\n");
        }
    }
    return 0;
}