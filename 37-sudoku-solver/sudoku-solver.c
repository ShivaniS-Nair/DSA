#include <stdbool.h>

static int rows[9];
static int cols[9];
static int boxes[9];
static int emptyCells[81][2];
static int emptyCount;

static bool backtrack(char** board, int idx) {
    if (idx == emptyCount) {
        return true; // All empty cells filled validly
    }

    int r = emptyCells[idx][0];
    int c = emptyCells[idx][1];
    int boxIdx = (r / 3) * 3 + (c / 3);

    // Bits set to 1 represent digits 1..9 that are ALREADY used
    int used = rows[r] | cols[c] | boxes[boxIdx];

    for (int d = 0; d < 9; d++) {
        int bit = 1 << d;
        if ((used & bit) == 0) {
            // Place digit
            board[r][c] = (char)('1' + d);
            rows[r] |= bit;
            cols[c] |= bit;
            boxes[boxIdx] |= bit;

            if (backtrack(board, idx + 1)) {
                return true;
            }

            // Undo placement (backtrack)
            rows[r] ^= bit;
            cols[c] ^= bit;
            boxes[boxIdx] ^= bit;
            board[r][c] = '.';
        }
    }

    return false;
}

void solveSudoku(char** board, int boardSize, int* boardColSize) {
    emptyCount = 0;
    for (int i = 0; i < 9; i++) {
        rows[i] = 0;
        cols[i] = 0;
        boxes[i] = 0;
    }

    // Initialize bitmasks with pre-filled digits and list empty cells
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            char ch = board[r][c];
            if (ch == '.') {
                emptyCells[emptyCount][0] = r;
                emptyCells[emptyCount][1] = c;
                emptyCount++;
            } else {
                int bit = 1 << (ch - '1');
                int boxIdx = (r / 3) * 3 + (c / 3);
                rows[r] |= bit;
                cols[c] |= bit;
                boxes[boxIdx] |= bit;
            }
        }
    }

    backtrack(board, 0);
}
