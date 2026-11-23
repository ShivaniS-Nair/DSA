#include <stdbool.h>

bool dfs(char** board, int rows, int cols, int r, int c, char* word, int idx) {
    // Base case: matched all characters in word
    if (word[idx] == '\0') {
        return true;
    }

    // Boundary check and character mismatch check
    if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != word[idx]) {
        return false;
    }

    // Save current character and mark cell as visited in-place
    char temp = board[r][c];
    board[r][c] = '#';

    // Explore all 4 adjacent directions (down, up, right, left)
    bool found = dfs(board, rows, cols, r + 1, c, word, idx + 1) ||
                 dfs(board, rows, cols, r - 1, c, word, idx + 1) ||
                 dfs(board, rows, cols, r, c + 1, word, idx + 1) ||
                 dfs(board, rows, cols, r, c - 1, word, idx + 1);

    // Backtrack: restore the original character
    board[r][c] = temp;

    return found;
}

bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    int rows = boardSize;
    int cols = boardColSize[0];

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (board[r][c] == word[0] && dfs(board, rows, cols, r, c, word, 0)) {
                return true;
            }
        }
    }

    return false;
}
