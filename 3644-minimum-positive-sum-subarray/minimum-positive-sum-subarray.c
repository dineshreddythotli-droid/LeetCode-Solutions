
int minimumSumSubarray(int* nums, int numsSize, int l, int r) {
    int min_sum = INT_MAX;

    for (int len = l; len <= r; len++) {
        int current_sum = 0;

        // Calculate the sum of the initial window of size 'len'
        for (int i = 0; i < len; i++) {
            current_sum += nums[i];
        }

        if (current_sum > 0 && current_sum < min_sum) {
            min_sum = current_sum;
        }

        // Slide the window across the rest of the array
        for (int i = len; i < numsSize; i++) {
            current_sum += nums[i] - nums[i - len];
            if (current_sum > 0 && current_sum < min_sum) {
                min_sum = current_sum;
            }
        }
    }

    return (min_sum == INT_MAX) ? -1 : min_sum;
}