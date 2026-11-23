#include <stdlib.h>
#include <string.h>

static int catalan(int n) {
    long long c = 1;
    for (int i = 1; i <= n; i++) {
        c = c * 2 * (2 * i - 1) / (i + 1);
    }
    return (int)c;
}

static void backtrack(char** res, int* returnSize, char* current, int pos, int open, int close, int n) {
    if (pos == 2 * n) {
        current[pos] = '\0';
        char* copy = (char*)malloc((2 * n + 1) * sizeof(char));
        memcpy(copy, current, 2 * n + 1);
        res[(*returnSize)++] = copy;
        return;
    }

    if (open < n) {
        current[pos] = '(';
        backtrack(res, returnSize, current, pos + 1, open + 1, close, n);
    }

    if (close < open) {
        current[pos] = ')';
        backtrack(res, returnSize, current, pos + 1, open, close + 1, n);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** generateParenthesis(int n, int* returnSize) {
    int total = catalan(n);
    char** res = (char**)malloc(total * sizeof(char*));
    char* current = (char*)malloc((2 * n + 1) * sizeof(char));

    *returnSize = 0;
    backtrack(res, returnSize, current, 0, 0, 0, n);

    free(current);
    return res;
}
