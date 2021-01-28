//
// Created by NBao on 2021/01/28.
//
// Input:
//     Sequence X = <x_1, x_2, ..., x_n> and Sequence Y = <y_1, y_2, ..., y_m>
// Output:
//     A Common Substring Z = <z_1, z_2, ..., z_l>,
//     let max|Z|,
//     s.t. <z_1, z_2, ..., z_l>
//         = <x_{i}, x_{i+1}, ..., x_{i+l-1},>
//         = <y_{j}, y_{j+1}, ..., y_{j+l-1},>
//     (1 <= i <= n - l + 1; 1 <= j <= m - l + 1;)
//

#include <stdio.h>
#define LENGTH_X 7
#define LENGTH_Y 6

char X[LENGTH_X + 1] = {'\0', 'A', 'B', 'C', 'B', 'D', 'A', 'B'};
char Y[LENGTH_Y + 1] = {'\0', 'B', 'D', 'C' ,'A', 'B', 'A'};
int dp[LENGTH_X + 1][LENGTH_Y + 1];

int main() {
    int length_max = 0;
    int position_max = 0;

    for (int i = 0; i <= LENGTH_X; i++) {
        dp[i][0] = 0;
    }
    for (int i = 0; i <= LENGTH_Y; i++) {
        dp[0][i] = 0;
    }

    for (int i = 1; i <= LENGTH_X; i++) {
        for (int j = 1; j <= LENGTH_Y; j++) {
            if (X[i] != Y[j]) {
                dp[i][j] = 0;
            }
            else {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > length_max) {
                    length_max = dp[i][j];
                    position_max = i;
                }
            }
        }
    }

    if (length_max == 0) {
        printf("No Common Substrings\n");
    }
    else {
        for (int i = position_max - length_max + 1; i <= position_max; i++) {
            printf("%c", X[i]);
        }
        printf("\n");
    }
    return 0;
}

