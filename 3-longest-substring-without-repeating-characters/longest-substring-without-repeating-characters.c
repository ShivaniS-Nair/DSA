#include <string.h>

int lengthOfLongestSubstring(char* s) {
    // Array to store the last seen index of each ASCII character
    int lastSeen[128];
    
    // Initialize all entries to -1 (indicating not seen yet)
    memset(lastSeen, -1, sizeof(lastSeen));
    
    int maxLen = 0;
    int left = 0;
    
    for (int right = 0; s[right] != '\0'; right++) {
        unsigned char currentChar = s[right];
        
        // If the character was seen inside the current window, jump 'left' past it
        if (lastSeen[currentChar] >= left) {
            left = lastSeen[currentChar] + 1;
        }
        
        // Update the character's latest index
        lastSeen[currentChar] = right;
        
        // Calculate current window length and update maxLen
        int currentLen = right - left + 1;
        if (currentLen > maxLen) {
            maxLen = currentLen;
        }
    }
    
    return maxLen;
}
