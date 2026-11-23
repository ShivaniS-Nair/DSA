#include <stdbool.h>

bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    int rows[9] = {0};
    int cols[9] = {0};
    int boxes[9] = {0};

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            char ch = board[r][c];
            if (ch == '.') {
                continue;
            }

            int bit = 1 << (ch - '1');
            int boxIdx = (r / 3) * 3 + (c / 3);

            // Check if this digit already exists in the current row, column, or 3x3 box
            if ((rows[r] & bit) || (cols[c] & bit) || (boxes[boxIdx] & bit)) {
                return false;
            }

            // Mark the digit as seen
            rows[r] |= bit;
            cols[c] |= bit;
            boxes[boxIdx] |= bit;
        }
    }

    return true;
}
