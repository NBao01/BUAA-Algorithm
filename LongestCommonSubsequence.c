//
// Created by NBao on 2021/01/28.
//
// Input:
//     Sequence X = <x_1, x_2, ..., x_n> and Sequence Y = <y_1, y_2, ..., y_n>
// Output:
//     A Common Subsequence Z = <z_1, z_2, ..., z_l>,
//     let max|Z|,
//     s.t. <z_1, z_2, ..., z_l>
//         = <x_{i_1}, x_{i_2}, ..., x_{i_l},>
//         = <y_{j_1}, y_{j_2}, ..., y_{j_l},>
//     (1 <= i_1 < i_2 < ... < i_l <= n; 1 <= j_1 < j_2 < ... < j_l <= n;)
//

#include <stdio.h>
#define LENGTH_X 7
#define LENGTH_Y 6

// value stored in rec
#define L 1
#define U 2
#define LU 3

char X[LENGTH_X + 1] = {'\0', 'A', 'B', 'C', 'B', 'D', 'A', 'B'};
char Y[LENGTH_Y + 1] = {'\0', 'B', 'D', 'C' ,'A', 'B', 'A'};
int dp[LENGTH_X + 1][LENGTH_Y + 1];
int rec[LENGTH_X + 1][LENGTH_Y + 1];

void Print_LCS(int i, int j) {
    if (i == 0 || j == 0) {
        return;
    }
    if (rec[i][j] == LU) {
        Print_LCS(i - 1, j - 1);
        printf("%c", X[i]);
    }
    else if (rec[i][j] == U) {
        Print_LCS(i - 1, j);
    }
    else {
        Print_LCS(i, j - 1);
    }
}

int main() {
    for (int i = 0; i <= LENGTH_X; i++) {
        dp[i][0] = 0;
    }
    for (int i = 0; i <= LENGTH_Y; i++) {
        dp[0][i] = 0;
    }

    for (int i = 1; i <= LENGTH_X; i++) {
        for (int j = 1; j <= LENGTH_Y; j++) {
            if (X[i] == Y[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                rec[i][j] = LU;
            }
            else if (dp[i - 1][j] >= dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
                rec[i][j] = U;
            }
            else {
                dp[i][j] = dp[i][j - 1];
                rec[i][j] = L;
            }
        }
    }

    Print_LCS(LENGTH_X, LENGTH_Y);
    printf("\n");
    return 0;
}

