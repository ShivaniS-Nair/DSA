#include <limits.h>

static int maxInt(int a, int b) {
    return (a > b) ? a : b;
}

static int maxCrossingSum(int* nums, int left, int mid, int right) {
    // Best suffix sum ending at mid
    int leftSum = INT_MIN;
    int sum = 0;
    for (int i = mid; i >= left; i--) {
        sum += nums[i];
        if (sum > leftSum) {
            leftSum = sum;
        }
    }

    // Best prefix sum starting at mid + 1
    int rightSum = INT_MIN;
    sum = 0;
    for (int i = mid + 1; i <= right; i++) {
        sum += nums[i];
        if (sum > rightSum) {
            rightSum = sum;
        }
    }

    return leftSum + rightSum;
}

static int divideAndConquer(int* nums, int left, int right) {
    if (left == right) {
        return nums[left];
    }

    int mid = left + (right - left) / 2;

    int leftBest = divideAndConquer(nums, left, mid);
    int rightBest = divideAndConquer(nums, mid + 1, right);
    int crossBest = maxCrossingSum(nums, left, mid, right);

    return maxInt(maxInt(leftBest, rightBest), crossBest);
}

int maxSubArray(int* nums, int numsSize) {
    return divideAndConquer(nums, 0, numsSize - 1);
}

