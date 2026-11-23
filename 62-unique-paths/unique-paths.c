int uniquePaths(int m, int n) {
    int dp[100];

    // Base case: the top row has exactly 1 way to reach each cell
    for (int c = 0; c < n; c++) {
        dp[c] = 1;
    }

    // Update row by row: dp[c] (new) = dp[c] (from top) + dp[c - 1] (from left)
    for (int r = 1; r < m; r++) {
        for (int c = 1; c < n; c++) {
            dp[c] += dp[c - 1];
        }
    }

    return dp[n - 1];
}
