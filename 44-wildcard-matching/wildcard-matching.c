#include <stdbool.h>

bool isMatch(char* s, char* p) {
    int sIdx = 0;
    int pIdx = 0;
    int starIdx = -1;
    int matchIdx = 0;

    while (s[sIdx] != '\0') {
        // 1. Direct character match or '?' single-character wildcard
        if (p[pIdx] == '?' || p[pIdx] == s[sIdx]) {
            sIdx++;
            pIdx++;
        }
        // 2. Record '*' position and initially match zero characters
        else if (p[pIdx] == '*') {
            starIdx = pIdx;
            matchIdx = sIdx;
            pIdx++;
        }
        // 3. Mismatch: backtrack to the last '*', absorbing one more character from s
        else if (starIdx != -1) {
            pIdx = starIdx + 1;
            matchIdx++;
            sIdx = matchIdx;
        }
        // 4. Mismatch with no prior '*' to fall back on
        else {
            return false;
        }
    }

    // Consume any trailing '*' wildcards in p (each can match an empty sequence)
    while (p[pIdx] == '*') {
        pIdx++;
    }

    return p[pIdx] == '\0';
}
