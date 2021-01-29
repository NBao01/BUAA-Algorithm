//
// Created by NBao on 2021/01/28.
//
// Input:
//     String s with length n, String t with length m
// Output:
//     A series of edit operations O = <e_1, e_2, ..., e_d>
//     let min|O|, s.t. String s is equal to String t After the operation O
//

#include <stdio.h>
#define LENGTH_S 7
#define LENGTH_T 6
#define MIN(a, b, c) ((a) < (b)? ((a) < (c)? (a) : (c)) : ((b) < (c)? (b):(c)))

// value stored in rec
#define L 1
#define U 2
#define LU 3

char S[LENGTH_S + 1] = {'\0', 'A', 'B', 'C', 'B', 'D', 'A', 'B'};
char T[LENGTH_T + 1] = {'\0', 'B', 'D', 'C' ,'A', 'B', 'A'};
int dp[LENGTH_S + 1][LENGTH_T + 1];
int rec[LENGTH_S + 1][LENGTH_T + 1];

void Print_MED(int i, int j) {
    if (i == 0 && j == 0) {
        return;
    }
    if (rec[i][j] == LU) {
        Print_MED(i - 1, j - 1);
        if (S[i] == T[j]) {
            printf("No operation\n");
        }
        else {
            printf("Replace %c with %c\n", S[i], T[j]);
        }
    }
    else if (rec[i][j] == U) {
        Print_MED(i - 1, j);
        printf("Delete %c\n", S[i]);
    }
    else {
        Print_MED(i, j - 1);
        printf("Insert %c\n", T[j]);
    }
}

int main() {
    for (int i = 0; i <= LENGTH_S; i++) {
        dp[i][0] = i;
        rec[i][0] = U;
    }
    for (int i = 0; i <= LENGTH_T; i++) {
        dp[0][i] = i;
        rec[0][i] = L;
    }

    for (int i = 1; i <= LENGTH_S; i++) {
        for (int j = 1; j <= LENGTH_T; j++) {
            int c = 0;
            if (S[i] != T[j]) {
                c = 1;
            }
            int replace = dp[i - 1][j - 1] + c;
            int delete = dp[i - 1][j];
            int insert = dp[i][j - 1];
            if (replace == MIN(replace, delete, insert)) {
                dp[i][j] = dp[i - 1][j - 1] + c;
                rec[i][j] = LU;
            }
            else if (insert == MIN(replace, delete, insert)) {
                dp[i][j] = dp[i][j - 1] + 1;
                rec[i][j] = L;
            }
            else {
                dp[i][j] = dp[i - 1][j] + 1;
                rec[i][j] = U;
            }
        }
    }

    Print_MED(LENGTH_S, LENGTH_T);
    return 0;
}