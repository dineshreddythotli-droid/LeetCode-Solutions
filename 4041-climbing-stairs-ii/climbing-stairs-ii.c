int climbStairs(int n, int* costs, int costsSize) {
    int dp[n + 1];

    for (int i = 0; i <= n; i++) {
        dp[i] = INT_MAX / 2;
    }

    dp[0] = 0;

    for (int i = 1; i <= n; i++) {

        for (int j = i - 3; j < i; j++) {

            if (j >= 0) {
                int jump = i - j;

                int total = dp[j] + costs[i - 1] + jump * jump;

                if (total < dp[i]) {
                    dp[i] = total;
                }
            }
        }
    }

    return dp[n];
}