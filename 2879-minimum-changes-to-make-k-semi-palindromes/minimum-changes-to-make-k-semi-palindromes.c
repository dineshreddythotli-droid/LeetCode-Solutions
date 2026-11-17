
#define INF 1000000

int minimumChanges(char* s, int k) {
    int n = strlen(s);

    int cost[205][205];

    // Step 1: Precompute the cost of every substring.
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            int len = j - i + 1;
            cost[i][j] = INF;

            // Try every proper divisor of len.
            for (int d = 1; d < len; d++) {

                if (len % d != 0)
                    continue;

                int changes = 0;

                // Compare characters in each group.
                for (int offset = 0; offset < d; offset++) {

                    int left = i + offset;
                    int right = j - d + 1 + offset;

                    while (left < right) {

                        if (s[left] != s[right])
                            changes++;

                        left += d;
                        right -= d;
                    }
                }

                if (changes < cost[i][j])
                    cost[i][j] = changes;
            }
        }
    }

    // Step 2: DP initialization.
    int dp[205][205];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = INF;
        }
    }

    dp[0][0] = 0;

    // Step 3: Calculate minimum partition cost.
    for (int parts = 1; parts <= k; parts++) {

        for (int i = 2 * parts; i <= n; i++) {

            for (int start = 2 * (parts - 1);
                 start <= i - 2; start++) {

                if (dp[start][parts - 1] == INF)
                    continue;

                int newCost = dp[start][parts - 1]
                            + cost[start][i - 1];

                if (newCost < dp[i][parts])
                    dp[i][parts] = newCost;
            }
        }
    }

    return dp[n][k];
}