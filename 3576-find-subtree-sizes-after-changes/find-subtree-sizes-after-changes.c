#include <stdlib.h>
#include <string.h>

void dfs(int u, const int* parent, const char* s, const int* head,
         const int* next, int* lastSeen, int* ans) {
    int ch = s[u] - 'a';
    int prevAncestor = lastSeen[ch];

    // Record current node as the closest ancestor for its character
    lastSeen[ch] = u;

    // Process all children in the original tree
    for (int v = head[u]; v != -1; v = next[v]) {
        dfs(v, parent, s, head, next, lastSeen, ans);
    }

    // Backtrack: restore the previous ancestor for this character
    lastSeen[ch] = prevAncestor;

    // Add finalized subtree size of u to its target parent
    if (u != 0) {
        int targetParent = (prevAncestor != -1) ? prevAncestor : parent[u];
        ans[targetParent] += ans[u];
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findSubtreeSizes(int* parent, int parentSize, char* s, int* returnSize) {
    int n = parentSize;
    *returnSize = n;

    int* ans = (int*)malloc(n * sizeof(int));
    int* head = (int*)malloc(n * sizeof(int));
    int* next = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        ans[i] = 1;
        head[i] = -1;
    }

    // Build adjacency list for the original tree
    for (int i = 1; i < n; i++) {
        int p = parent[i];
        next[i] = head[p];
        head[p] = i;
    }

    int lastSeen[26];
    for (int i = 0; i < 26; i++) {
        lastSeen[i] = -1;
    }

    dfs(0, parent, s, head, next, lastSeen, ans);

    free(head);
    free(next);

    return ans;
}
