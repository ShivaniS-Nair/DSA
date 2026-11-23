#include <stdlib.h>

static int largestRectangleArea(int* heights, int cols, int* stack) {
    int top = -1;
    int maxArea = 0;

    for (int i = 0; i <= cols; i++) {
        int currHeight = (i == cols) ? 0 : heights[i];

        while (top != -1 && currHeight < heights[stack[top]]) {
            int h = heights[stack[top--]];
            int width = (top == -1) ? i : (i - stack[top] - 1);
            int area = h * width;
            if (area > maxArea) {
                maxArea = area;
            }
        }

        stack[++top] = i;
    }

    return maxArea;
}

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize) {
    if (matrixSize == 0 || matrixColSize == NULL || matrixColSize[0] == 0) {
        return 0;
    }

    int cols = matrixColSize[0];
    int* heights = (int*)calloc(cols, sizeof(int));
    int* stack = (int*)malloc((cols + 1) * sizeof(int));
    int maxRect = 0;

    for (int r = 0; r < matrixSize; r++) {
        for (int c = 0; c < cols; c++) {
            heights[c] = (matrix[r][c] == '1') ? (heights[c] + 1) : 0;
        }

        int rowMax = largestRectangleArea(heights, cols, stack);
        if (rowMax > maxRect) {
            maxRect = rowMax;
        }
    }

    free(heights);
    free(stack);
    return maxRect;
}
