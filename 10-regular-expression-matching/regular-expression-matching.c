#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isMatch(char* s, char* p) {
    int m = strlen(s);
    int n = strlen(p);

    // dp[i][j] represents if s[0...i-1] matches p[0...j-1]
    bool dp[m + 1][n + 1];
    memset(dp, false, sizeof(dp));

    // Base case: empty string matches empty pattern
    dp[0][0] = true;

    // Handle patterns like a*, a*b*, or .* that can match an empty string
    for (int j = 2; j <= n; j++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }

    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                // Direct character match or '.' wildcard
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                // Case 1: '*' matches zero occurrences of the preceding element
                dp[i][j] = dp[i][j - 2];

                // Case 2: '*' matches one or more occurrences if preceding char matches
                if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            }
        }
    }

    return dp[m][n];
}
