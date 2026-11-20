#include <stdlib.h>

// Comparator function for qsort (avoids integer overflow)
int compare(const void* a, const void* b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    return (int_a > int_b) - (int_a < int_b);
}

int threeSumClosest(int* nums, int numsSize, int target) {
    // 1. Sort the array in ascending order
    qsort(nums, numsSize, sizeof(int), compare);

    // Initialize closest sum with the first valid triplet
    int closestSum = nums[0] + nums[1] + nums[2];

    // 2. Fix the first element and scan the rest with two pointers
    for (int i = 0; i < numsSize - 2; i++) {
        // Optional optimization: skip duplicate starting elements
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }

        int left = i + 1;
        int right = numsSize - 1;

        while (left < right) {
            int currentSum = nums[i] + nums[left] + nums[right];

            // Exact match gives a difference of 0, which cannot be beaten
            if (currentSum == target) {
                return currentSum;
            }

            // Update closestSum if currentSum is closer to target
            if (abs(currentSum - target) < abs(closestSum - target)) {
                closestSum = currentSum;
            }

            // Move pointers based on comparison with target
            if (currentSum < target) {
                left++;
            } else {
                right--;
            }
        }
    }

    return closestSum;
}
