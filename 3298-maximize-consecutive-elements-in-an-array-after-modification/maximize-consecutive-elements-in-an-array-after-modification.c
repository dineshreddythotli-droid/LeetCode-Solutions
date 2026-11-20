
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int maxSelectedElements(int* nums, int numsSize) {
    // 1. Sort the array in ascending order
    qsort(nums, numsSize, sizeof(int), compare);
    
    // Max possible element value is 10^6; +1 for increment, +1 for 0-indexing
    int max_val = nums[numsSize - 1] + 2;
    int* dp = (int*)calloc(max_val, sizeof(int));
    if (!dp) return 0;

    int max_len = 0;

    // 2. Process each element in sorted order
    for (int i = 0; i < numsSize; i++) {
        int x = nums[i];
        
        // Option A: Increment x to (x + 1), extending a sequence ending at x
        // Must be updated BEFORE dp[x] so the same element isn't used twice
        if (dp[x] + 1 > dp[x + 1]) {
            dp[x + 1] = dp[x] + 1;
        }
        
        // Option B: Keep x as is, extending a sequence ending at (x - 1)
        if (dp[x - 1] + 1 > dp[x]) {
            dp[x] = dp[x - 1] + 1;
        }

        // Update the global maximum
        if (dp[x] > max_len) max_len = dp[x];
        if (dp[x + 1] > max_len) max_len = dp[x + 1];
    }

    free(dp);
    return max_len;
}