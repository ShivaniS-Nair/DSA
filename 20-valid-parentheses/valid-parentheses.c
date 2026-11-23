#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isValid(char* s) {
    int n = strlen(s);
    // An odd-length string can never be balanced
    if (n % 2 != 0) {
        return false;
    }

    char* stack = (char*)malloc(n * sizeof(char));
    int top = -1;

    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == '(') {
            stack[++top] = ')';
        } else if (c == '{') {
            stack[++top] = '}';
        } else if (c == '[') {
            stack[++top] = ']';
        } else {
            // Mismatch or closing bracket with no matching opening bracket
            if (top == -1 || stack[top--] != c) {
                free(stack);
                return false;
            }
        }
    }

    bool valid = (top == -1);
    free(stack);
    return valid;
}
