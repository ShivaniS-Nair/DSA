#include <stdlib.h>
#include <string.h>

char* intToRoman(int num) {
    // 13 possible standard + subtractive values in descending order
    int values[] = {
        1000, 900, 500, 400, 
        100,  90,  50,  40, 
        10,   9,   5,   4, 
        1
    };
    
    const char* symbols[] = {
        "M",  "CM", "D",  "CD", 
        "C",  "XC", "L",  "XL", 
        "X",  "IX", "V",  "IV", 
        "I"
    };

    // Max length for num <= 3999 is 15 characters (3888 -> "MMMDCCCLXXXVIII") + 1 null terminator
    char* result = (char*)malloc(16 * sizeof(char));
    result[0] = '\0';

    for (int i = 0; i < 13 && num > 0; i++) {
        while (num >= values[i]) {
            strcat(result, symbols[i]);
            num -= values[i];
        }
    }

    return result;
}
