#include <limits.h>
#include <ctype.h>

int myAtoi(char* s) {
    int i = 0;
    int sign = 1;
    int result = 0;

    // 1. Skip leading whitespace
    while (s[i] == ' ') {
        i++;
    }

    // 2. Check for optional '+' or '-' sign
    if (s[i] == '+' || s[i] == '-') {
        if (s[i] == '-') {
            sign = -1;
        }
        i++;
    }

    // 3. Convert digits and check for 32-bit overflow before updating result
    while (isdigit(s[i])) {
        int digit = s[i] - '0';

        // Check if multiplying by 10 and adding digit will exceed INT_MAX
        if (result > (INT_MAX - digit) / 10) {
            return (sign == 1) ? INT_MAX : INT_MIN;
        }

        result = result * 10 + digit;
        i++;
    }

    return result * sign;
}
