#include <stdbool.h>
#include <stdlib.h>

static int findBound(int* nums, int numsSize, int target, bool isFirst) {
    int left = 0;
    int right = numsSize - 1;
    int bound = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) {
            bound = mid;
            if (isFirst) {
                right = mid - 1; // Keep searching the left half
            } else {
                left = mid + 1;  // Keep searching the right half
            }
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return bound;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* res = (int*)malloc(2 * sizeof(int));
    res[0] = -1;
    res[1] = -1;

    if (numsSize == 0) {
        return res;
    }

    int first = findBound(nums, numsSize, target, true);
    // Early exit: if target does not exist at all, skip the second binary search
    if (first == -1) {
        return res;
    }

    res[0] = first;
    res[1] = findBound(nums, numsSize, target, false);
    return res;
}
