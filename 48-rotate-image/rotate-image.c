static void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void rotate(int** matrix, int matrixSize, int* matrixColSize) {
    int n = matrixSize;

    // 1. Transpose the matrix across the main diagonal (top-left to bottom-right)
    for (int r = 0; r < n; r++) {
        for (int c = r + 1; c < n; c++) {
            swap(&matrix[r][c], &matrix[c][r]);
        }
    }

    // 2. Reverse each row horizontally
    for (int r = 0; r < n; r++) {
        int left = 0;
        int right = n - 1;
        while (left < right) {
            swap(&matrix[r][left], &matrix[r][right]);
            left++;
            right--;
        }
    }
}

