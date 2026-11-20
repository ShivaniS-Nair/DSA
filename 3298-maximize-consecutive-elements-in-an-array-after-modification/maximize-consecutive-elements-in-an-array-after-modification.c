#include <stdlib.h>

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int maxSelectedElements(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), cmp);

    // Max value in nums can be 10^6, incremented to 10^6 + 1
    int maxVal = nums[numsSize - 1] + 2;
    int* dp = (int*)calloc(maxVal, sizeof(int));
    int ans = 0;

    for (int i = 0; i < numsSize; i++) {
        int x = nums[i];
        
        // Update x + 1 first so it uses the previous state of dp[x]
        if (dp[x] + 1 > dp[x + 1]) {
            dp[x + 1] = dp[x] + 1;
        }
        if (dp[x - 1] + 1 > dp[x]) {
            dp[x] = dp[x - 1] + 1;
        }

        if (dp[x] > ans) ans = dp[x];
        if (dp[x + 1] > ans) ans = dp[x + 1];
    }

    free(dp);
    return ans;
}
