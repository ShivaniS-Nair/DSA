#include <stdlib.h>
#include <string.h>

static int nChooseK(int n, int k) {
    if (k > n - k) {
        k = n - k;
    }
    long long res = 1;
    for (int i = 1; i <= k; i++) {
        res = res * (n - k + i) / i;
    }
    return (int)res;
}

static void backtrack(int n, int k, int start, int* path, int depth,
                      int** res, int* returnSize, int* returnColumnSizes) {
    if (depth == k) {
        int* comb = (int*)malloc(k * sizeof(int));
        memcpy(comb, path, k * sizeof(int));
        res[*returnSize] = comb;
        returnColumnSizes[*returnSize] = k;
        (*returnSize)++;
        return;
    }

    // Need (k - depth) more numbers; largest valid starting number is n - (k - depth) + 1
    int limit = n - (k - depth) + 1;
    for (int i = start; i <= limit; i++) {
        path[depth] = i;
        backtrack(n, k, i + 1, path, depth + 1, res, returnSize, returnColumnSizes);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combine(int n, int k, int* returnSize, int** returnColumnSizes) {
    int total = nChooseK(n, k);
    int** res = (int**)malloc(total * sizeof(int*));
    *returnColumnSizes = (int*)malloc(total * sizeof(int));
    *returnSize = 0;

    // Under problem constraints (1 <= k <= n <= 20), path fits cleanly on the stack
    int path[20];
    backtrack(n, k, 1, path, 0, res, returnSize, *returnColumnSizes);

    return res;
}
