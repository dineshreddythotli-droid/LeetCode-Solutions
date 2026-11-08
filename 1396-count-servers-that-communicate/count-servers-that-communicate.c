int countServers(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];

    int rowCount[250] = {0};
    int colCount[250] = {0};

    // Count servers in each row and column
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) {
                rowCount[i]++;
                colCount[j]++;
            }
        }
    }

    int result = 0;

    // Count servers that can communicate
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1 &&
                (rowCount[i] > 1 || colCount[j] > 1)) {
                result++;
            }
        }
    }

    return result;
}