#include <stdlib.h>

static int cmpInterval(const void* a, const void* b) {
    const int* intervalA = *(const int* const*)a;
    const int* intervalB = *(const int* const*)b;

    if (intervalA[0] != intervalB[0]) {
        return (intervalA[0] > intervalB[0]) - (intervalA[0] < intervalB[0]);
    }
    return (intervalA[1] > intervalB[1]) - (intervalA[1] < intervalB[1]);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
            int* returnSize, int** returnColumnSizes) {
    if (intervalsSize == 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    // 1. Sort intervals in ascending order by start time (and end time on ties)
    qsort(intervals, intervalsSize, sizeof(int*), cmpInterval);

    int** res = (int**)malloc(intervalsSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(intervalsSize * sizeof(int));

    // 2. Initialize the output with the first sorted interval
    res[0] = (int*)malloc(2 * sizeof(int));
    res[0][0] = intervals[0][0];
    res[0][1] = intervals[0][1];
    (*returnColumnSizes)[0] = 2;
    int count = 1;

    // 3. Scan remaining intervals and merge whenever current start <= last merged end
    for (int i = 1; i < intervalsSize; i++) {
        int currStart = intervals[i][0];
        int currEnd = intervals[i][1];
        int lastEnd = res[count - 1][1];

        if (currStart <= lastEnd) {
            if (currEnd > lastEnd) {
                res[count - 1][1] = currEnd;
            }
        } else {
            res[count] = (int*)malloc(2 * sizeof(int));
            res[count][0] = currStart;
            res[count][1] = currEnd;
            (*returnColumnSizes)[count] = 2;
            count++;
        }
    }

    *returnSize = count;
    return res;
}
