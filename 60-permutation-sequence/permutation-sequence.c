#include <stdlib.h>

/**
 * Note: The returned string must be malloced, assume caller calls free().
 */
char* getPermutation(int n, int k) {
    int fact[10];
    int nums[9];

    // 1. Precompute factorials 0! .. n! and populate available digits 1 .. n
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
        nums[i - 1] = i;
    }

    char* res = (char*)malloc((n + 1) * sizeof(char));
    k--; // Convert k to 0-based indexing

    // 2. Pick each digit directly using integer division by (i - 1)!
    for (int i = n; i >= 1; i--) {
        int blockSize = fact[i - 1];
        int idx = k / blockSize;

        res[n - i] = (char)('0' + nums[idx]);

        // Remove the chosen digit by shifting subsequent elements left
        for (int j = idx; j < i - 1; j++) {
            nums[j] = nums[j + 1];
        }

        k %= blockSize;
    }

    res[n] = '\0';
    return res;
}
