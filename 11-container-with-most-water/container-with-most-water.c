int maxArea(int* height, int heightSize) {
    int left = 0;
    int right = heightSize - 1;
    int max_water = 0;

    while (left < right) {
        // Width is the distance between the two pointers
        int width = right - left;
        
        // Height is limited by the shorter vertical line
        int min_height = (height[left] < height[right]) ? height[left] : height[right];
        
        // Calculate current area and update maximum
        int current_water = width * min_height;
        if (current_water > max_water) {
            max_water = current_water;
        }

        // Move the pointer pointing to the shorter line inward
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }

    return max_water;
}
