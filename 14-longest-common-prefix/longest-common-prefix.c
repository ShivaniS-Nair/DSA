#include <stdlib.h>
#include <string.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0) {
        return "";
    }

    // Iterate through each character of the first string
    for (int i = 0; strs[0][i] != '\0'; i++) {
        char currentChar = strs[0][i];

        // Compare this character with the same index in all other strings
        for (int j = 1; j < strsSize; j++) {
            // Stop if we reach the end of string j OR find a mismatch
            if (strs[j][i] == '\0' || strs[j][i] != currentChar) {
                // Allocate memory for the prefix (+1 for the null terminator)
                char* result = (char*)malloc((i + 1) * sizeof(char));
                strncpy(result, strs[0], i);
                result[i] = '\0';
                return result;
            }
        }
    }

    // If the entire first string matches, return a copy of it
    char* result = (char*)malloc((strlen(strs[0]) + 1) * sizeof(char));
    strcpy(result, strs[0]);
    return result;
}
