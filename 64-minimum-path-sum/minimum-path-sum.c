#define MAX_COLS 200

static int minInt(int a, int b) {
    return (a < b) ? a : b;
}

int minPathSum(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = *gridColSize;
    int dp[MAX_COLS];

    // 1. Initialize the top row via cumulative horizontal prefix sums
    dp[0] = grid[0][0];
    for (int c = 1; c < cols; c++) {
        dp[c] = dp[c - 1] + grid[0][c];
    }

    // 2. Process remaining rows top-to-bottom
    for (int r = 1; r < rows; r++) {
        // First column can only be reached straight down from above
        dp[0] += grid[r][0];

        for (int c = 1; c < cols; c++) {
            dp[c] = grid[r][c] + minInt(dp[c], dp[c - 1]);
        }
    }

    return dp[cols - 1];
}

