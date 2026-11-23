int firstMissingPositive(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        // Keep swapping while nums[i] is in [1, numsSize] and not already at its target index
        while (nums[i] >= 1 && nums[i] <= numsSize && nums[nums[i] - 1] != nums[i]) {
            int targetIdx = nums[i] - 1;
            int temp = nums[targetIdx];
            nums[targetIdx] = nums[i];
            nums[i] = temp;
        }
    }

    // Find the first index whose value does not match i + 1
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }

    // All integers from 1 to numsSize are present
    return numsSize + 1;
}
