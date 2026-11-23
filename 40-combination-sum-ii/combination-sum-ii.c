#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LEN 30

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
        // Skip duplicate candidates at the same recursion depth
        if (i > startIdx && candidates[i] == candidates[i - 1]) {
            continue;
        }

        // Prune remaining branches because candidates is sorted
        if (candidates[i] > remain) {
            break;
        }

        path[pathLen] = candidates[i];
        // Pass i + 1 so each element in candidates is used at most once
        backtrack(candidates, candidatesSize, remain - candidates[i], i + 1,
                  path, pathLen + 1, res, returnSize, returnColumnSizes, capacity);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum2(int* candidates, int candidatesSize, int target,
                      int* returnSize, int** returnColumnSizes) {
    qsort(candidates, candidatesSize, sizeof(int), cmpInt);

    int capacity = 64;
    int** res = (int**)malloc(capacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));
    *returnSize = 0;

    // Under problem constraints (candidates[i] >= 1, target <= 30), max depth is 30
    int path[MAX_PATH_LEN];
    backtrack(candidates, candidatesSize, target, 0,
              path, 0, &res, returnSize, returnColumnSizes, &capacity);

    return res;
}
