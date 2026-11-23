static int backtrack(int n, int row, int cols, int diag1, int diag2) {
    if (row == n) {
        return 1;
    }

    int count = 0;
    // Keep only the lowest n bits where no column or diagonal is under attack
    int available = ((1 << n) - 1) & ~(cols | diag1 | diag2);

    while (available != 0) {
        int bit = available & -available; // Isolate lowest available column bit
        count += backtrack(n, row + 1,
                           cols | bit,
                           (diag1 | bit) << 1,
                           (diag2 | bit) >> 1);
        available &= available - 1;       // Clear the tested column bit
    }

    return count;
}

int totalNQueens(int n) {
    return backtrack(n, 0, 0, 0, 0);
}
