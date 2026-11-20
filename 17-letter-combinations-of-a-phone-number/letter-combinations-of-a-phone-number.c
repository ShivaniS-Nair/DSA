#include <stdlib.h>
#include <string.h>

void backtrack(const char* digits, int index, int len, const char* map[], 
               char* current, char** result, int* count) {
    // Base case: full combination formed
    if (index == len) {
        result[*count] = (char*)malloc((len + 1) * sizeof(char));
        strcpy(result[*count], current);
        (*count)++;
        return;
    }

    // Explore all letters mapped to the current digit
    const char* letters = map[digits[index] - '0'];
    for (int i = 0; letters[i] != '\0'; i++) {
        current[index] = letters[i];
        backtrack(digits, index + 1, len, map, current, result, count);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** letterCombinations(char* digits, int* returnSize) {
    int len = strlen(digits);
    if (len == 0) {
        *returnSize = 0;
        return NULL;
    }

    const char* map[10] = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    // Calculate exact number of combinations to allocate memory once
    int capacity = 1;
    for (int i = 0; i < len; i++) {
        capacity *= strlen(map[digits[i] - '0']);
    }

    char** result = (char**)malloc(capacity * sizeof(char*));
    char* current = (char*)malloc((len + 1) * sizeof(char));
    current[len] = '\0';

    int count = 0;
    backtrack(digits, 0, len, map, current, result, &count);

    free(current);
    *returnSize = count;
    return result;
}
