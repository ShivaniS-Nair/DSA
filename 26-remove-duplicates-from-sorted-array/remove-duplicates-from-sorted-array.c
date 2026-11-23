int removeDuplicates(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }

    int insertPos = 1;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != nums[insertPos - 1]) {
            nums[insertPos] = nums[i];
            insertPos++;
        }
    }

    return insertPos;
}
