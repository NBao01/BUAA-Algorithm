//
// Created by NBao on 2021/01/25.
//
// Input: An array of reals A[1..n]
// The value of subarray A[i..j] is V(i, j) = \sum_{x=i}^{j} A(x)
// Find i <= j such that V(i, j) is maximized
//

#include <stdio.h>
#define MAX(a, b, c) ((a) > (b)? ((a) > (c)? (a) : (c)) : ((b) > (c)? (b):(c)))

int MCS(int Array[], int left, int right) {
    if (left == right) {
        return Array[left];
    }

    int mid = (left + right) / 2;

    int leftMCS = MCS(Array, left, mid);
    int rightMCS = MCS(Array, mid + 1, right);

    // Find MCS across left part and right part.
    int midMCS = Array[mid] + Array[mid + 1];
    int temp = midMCS;
    for (int i = mid - 1; i >= left; i--) {
        temp += Array[i];
        if (temp > midMCS) {
            midMCS = temp;
        }
    }
    temp = midMCS;
    for (int i = mid + 2; i <= right; i++) {
        temp += Array[i];
        if (temp > midMCS) {
            midMCS = temp;
        }
    }

    return MAX(leftMCS, rightMCS, midMCS);
}

int main() {
    int list[] = {-3, 2, 1, -4, 5, 2, -1, 3, -1};
    int value = MCS(list, 0, 8);
    printf("%d\n", value);
    return 0;
}
