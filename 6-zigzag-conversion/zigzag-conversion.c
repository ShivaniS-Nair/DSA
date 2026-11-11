#include <stdlib.h>
#include <string.h>

char* convert(char* s, int numRows) {
    int n = strlen(s);
    
    // Edge case: no zigzag pattern is formed if numRows is 1 or >= string length
    if (numRows <= 1 || numRows >= n) {
        char* res = (char*)malloc((n + 1) * sizeof(char));
        strcpy(res, s);
        return res;
    }

    char* res = (char*)malloc((n + 1) * sizeof(char));
    int pos = 0;
    int cycleLen = 2 * numRows - 2;

    for (int r = 0; r < numRows; r++) {
        for (int j = r; j < n; j += cycleLen) {
            // Append the main vertical column character
            res[pos++] = s[j];

            // For middle rows, append the diagonal character between vertical columns
            int diagIdx = j + cycleLen - 2 * r;
            if (r > 0 && r < numRows - 1 && diagIdx < n) {
                res[pos++] = s[diagIdx];
            }
        }
    }

    res[pos] = '\0'; // Null-terminate the C string
    return res;
}
