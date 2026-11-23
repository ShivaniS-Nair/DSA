
#include <stdbool.h>

bool canJump(int* nums, int numsSize) {
    int maxReach = 0;

    for (int i = 0; i < numsSize; i++) {
        // If the current index is beyond the furthest reachable position, we are stuck
        if (i > maxReach) {
            return false;
        }

        if (i + nums[i] > maxReach) {
            maxReach = i + nums[i];
        }

        // Early exit once the last index is guaranteed to be reachable
        if (maxReach >= numsSize - 1) {
            return true;
        }
    }

    return true;
}
