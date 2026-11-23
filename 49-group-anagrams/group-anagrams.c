#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* orig;
} WordEntry;

static int cmpChar(const void* a, const void* b) {
    return (*(const char*)a) - (*(const char*)b);
}

static int cmpEntry(const void* a, const void* b) {
    const WordEntry* ea = (const WordEntry*)a;
    const WordEntry* eb = (const WordEntry*)b;
    return strcmp(ea->key, eb->key);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (strsSize == 0) {
        *returnColumnSizes = NULL;
        return NULL;
    }

    // 1. Build (sorted key, original string) pairs
    WordEntry* entries = (WordEntry*)malloc(strsSize * sizeof(WordEntry));
    for (int i = 0; i < strsSize; i++) {
        int len = strlen(strs[i]);
        char* key = (char*)malloc((len + 1) * sizeof(char));
        memcpy(key, strs[i], len + 1);
        qsort(key, len, sizeof(char), cmpChar);

        entries[i].key = key;
        entries[i].orig = strs[i];
    }

    // 2. Sort all entries lexicographically by their canonical sorted key
    qsort(entries, strsSize, sizeof(WordEntry), cmpEntry);

    // 3. Group adjacent entries that share the same key
    char*** res = (char***)malloc(strsSize * sizeof(char**));
    *returnColumnSizes = (int*)malloc(strsSize * sizeof(int));

    int i = 0;
    while (i < strsSize) {
        int j = i + 1;
        while (j < strsSize && strcmp(entries[i].key, entries[j].key) == 0) {
            j++;
        }

        int groupSize = j - i;
        char** group = (char**)malloc(groupSize * sizeof(char*));
        for (int k = 0; k < groupSize; k++) {
            group[k] = entries[i + k].orig;
        }

        res[*returnSize] = group;
        (*returnColumnSizes)[*returnSize] = groupSize;
        (*returnSize)++;

        i = j;
    }

    // 4. Free temporary keys and entry array
    for (int idx = 0; idx < strsSize; idx++) {
        free(entries[idx].key);
    }
    free(entries);

    return res;
}
