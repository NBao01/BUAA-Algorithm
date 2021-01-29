//
// Created by NBao on 2021/01/29.
//
// Input:
//     Matrix-Chain U_{1..n} = <U_1, U_2, ..., U_n>
//     Dimensions p_0, p_1, ..., p_n, U_i's dimension is p_{i-1} * p_i
// Output:
//     Find a way to add parentheses to determine the calculation order
//     of matrix chain multiplication, so as to minimize the number of
//     matrix chain scalar multiplications
//

#include <stdio.h>
#include <string.h>

#define N 6

int p[N + 1] = {2, 3, 7, 9, 5, 2, 4};
int dp[N + 1][N + 1];
int rec[N + 1][N + 1];

void PrintMatrixChain(int i, int j) {
    if (i == j) {
        printf("U_%d", i);
        return;
    }
    printf("(");
    PrintMatrixChain(i, rec[i][j]);
    printf(")(");
    PrintMatrixChain(rec[i][j] + 1, j);
    printf(")");
}

int main() {
    memset(dp,0x3f,sizeof(dp)); // Initial dp[][] to infinity
    for (int i = 1; i <= N; i++) {
        dp[i][i] = 0;
    }
    for (int l = 2; l <= N; l++) {  // Traverse interval length from short to long
        for (int i = 1; i <= N - l + 1; i++) {  // Left Boundary
            int j = i + l - 1;  // Right Boundary
            for (int k = i; k <= j - 1; k++) {  // Traverse each k from i to j
                int q = dp[i][k] + dp[k + 1][j] + p[i - 1]* p[k] * p[j];
                if (q < dp[i][j]) {
                    dp[i][j] = q;
                    rec[i][j] = k;
                }
            }
        }
    }
    PrintMatrixChain(1, N);
    printf("\n");
    return 0;
}