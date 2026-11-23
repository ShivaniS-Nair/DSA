#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static int cmpInt(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

static void backtrack(int* nums, int numsSize, bool* used, int* path, int depth,
                      int** res, int* returnSize, int* returnColumnSizes) {
    if (depth == numsSize) {
        int* perm = (int*)malloc(numsSize * sizeof(int));
        memcpy(perm, path, numsSize * sizeof(int));
        res[*returnSize] = perm;
        returnColumnSizes[*returnSize] = numsSize;
        (*returnSize)++;
        return;
    }

    for (int i = 0; i < numsSize; i++) {
        if (used[i]) {
            continue;
        }
        // Skip duplicate value if its preceding identical element wasn't used at this level
        if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) {
            continue;
        }

        used[i] = true;
        path[depth] = nums[i];

        backtrack(nums, numsSize, used, path, depth + 1, res, returnSize, returnColumnSizes);

        used[i] = false; // Backtrack
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    qsort(nums, numsSize, sizeof(int), cmpInt);

    // Upper bound on unique permutations is n! (for n <= 8, 8! = 40,320)
    int maxPerms = 1;
    for (int i = 2; i <= numsSize; i++) {
        maxPerms *= i;
    }

    int** res = (int**)malloc(maxPerms * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxPerms * sizeof(int));
    *returnSize = 0;

    bool used[8] = {false};
    int path[8];

    backtrack(nums, numsSize, used, path, 0, res, returnSize, *returnColumnSizes);
    return res;
}
