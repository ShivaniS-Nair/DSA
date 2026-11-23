#include <stdlib.h>
#include <string.h>

static void backtrack(int n, int row, int cols, int diag1, int diag2,
                      int* queenCol, char**** res, int* returnSize,
                      int** returnColumnSizes, int* capacity) {
    if (row == n) {
        if (*returnSize == *capacity) {
            *capacity *= 2;
            *res = (char***)realloc(*res, (*capacity) * sizeof(char**));
            *returnColumnSizes = (int*)realloc(*returnColumnSizes, (*capacity) * sizeof(int));
        }

        char** board = (char**)malloc(n * sizeof(char*));
        for (int r = 0; r < n; r++) {
            board[r] = (char*)malloc((n + 1) * sizeof(char));
            memset(board[r], '.', n);
            board[r][queenCol[r]] = 'Q';
            board[r][n] = '\0';
        }

        (*res)[*returnSize] = board;
        (*returnColumnSizes)[*returnSize] = n;
        (*returnSize)++;
        return;
    }

    // Available column bits in the current row (lowest n bits)
    int available = ((1 << n) - 1) & ~(cols | diag1 | diag2);

    while (available != 0) {
        int bit = available & -available; // Isolate lowest available column bit
        int col = __builtin_ctz(bit);     // Convert bitmask to 0-indexed column

        queenCol[row] = col;
        backtrack(n, row + 1,
                  cols | bit,
                  (diag1 | bit) << 1,
                  (diag2 | bit) >> 1,
                  queenCol, res, returnSize, returnColumnSizes, capacity);

        available &= available - 1;       // Clear tested bit
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    // For n <= 9, the maximum number of solutions is 352 (at n = 9)
    int capacity = 64;
    char*** res = (char***)malloc(capacity * sizeof(char**));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));
    *returnSize = 0;

    int queenCol[9];
    backtrack(n, 0, 0, 0, 0, queenCol, &res, returnSize, returnColumnSizes, &capacity);

    return res;
}
