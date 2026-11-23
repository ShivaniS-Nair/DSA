#include <stdlib.h>
#include <string.h>

static int cmpInt(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

static void backtrack(int* candidates, int candidatesSize, int remain, int startIdx,
                      int* path, int pathLen, int*** res, int* returnSize,
                      int** returnColumnSizes, int* capacity) {
    if (remain == 0) {
        if (*returnSize == *capacity) {
            *capacity *= 2;
            *res = (int**)realloc(*res, (*capacity) * sizeof(int*));
            *returnColumnSizes = (int*)realloc(*returnColumnSizes, (*capacity) * sizeof(int));
        }

        int* comb = (int*)malloc(pathLen * sizeof(int));
        memcpy(comb, path, pathLen * sizeof(int));
        (*res)[*returnSize] = comb;
        (*returnColumnSizes)[*returnSize] = pathLen;
        (*returnSize)++;
        return;
    }

    for (int i = startIdx; i < candidatesSize; i++) {
        // Because candidates is sorted, no later element can fit in remain
        if (candidates[i] > remain) {
            break;
        }

        path[pathLen] = candidates[i];
        // Reuse index i because each candidate may be chosen unlimited times
        backtrack(candidates, candidatesSize, remain - candidates[i], i,
                  path, pathLen + 1, res, returnSize, returnColumnSizes, capacity);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum(int* candidates, int candidatesSize, int target,
                     int* returnSize, int** returnColumnSizes) {
    qsort(candidates, candidatesSize, sizeof(int), cmpInt);

    int capacity = 160; // Problem constraints guarantee fewer than 150 combinations
    int** res = (int**)malloc(capacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));
    *returnSize = 0;

    // Under constraints (candidates[i] >= 2, target <= 40), max combination length is 20
    int path[64];
    backtrack(candidates, candidatesSize, target, 0,
              path, 0, &res, returnSize, returnColumnSizes, &capacity);

    return res;
}
