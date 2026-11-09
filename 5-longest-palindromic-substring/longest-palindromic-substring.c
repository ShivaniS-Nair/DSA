#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to expand around the given indices and return the length of the palindrome
int expandAroundCenter(char* s, int left, int right, int len) {
    while (left >= 0 && right < len && s[left] == s[right]) {
        left--;
        right++;
    }
    // Returns the length of the valid palindrome found
    return right - left - 1;
}

char* longestPalindrome(char* s) {
    if (s == NULL || strlen(s) == 0) {
        char* empty = (char*)malloc(sizeof(char));
        *empty = '\0';
        return empty;
    }

    int n = strlen(s);
    int start = 0;
    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        // Case 1: Odd length palindromes (e.g., "aba" centered at 'b')
        int len1 = expandAroundCenter(s, i, i, n);
        
        // Case 2: Even length palindromes (e.g., "bb" centered between 'b' and 'b')
        int len2 = expandAroundCenter(s, i, i + 1, n);
        
        // Find the larger length out of the two cases
        int len = (len1 > len2) ? len1 : len2;

        // If a longer palindrome is found, update our boundaries
        if (len > maxLen) {
            maxLen = len;
            start = i - (len - 1) / 2;
        }
    }

    // Allocate memory for the result (+1 for the null terminator)
    char* result = (char*)malloc((maxLen + 1) * sizeof(char));
    strncpy(result, s + start, maxLen);
    result[maxLen] = '\0'; // Null-terminate the string

    return result;
}

