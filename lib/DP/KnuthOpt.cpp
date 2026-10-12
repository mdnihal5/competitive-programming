template <class Cost>
struct KnuthOpt {
    int n;
    vector<vector<int>> dp, opt;
    Cost cost;

    KnuthOpt(int n, Cost cost) : n(n), dp(n, vector<int>(n)), opt(n, vector<int>(n)), cost(cost) {
        for (int i = 0; i < n; i++) opt[i][i] = i;
        for (int len = 2; len <= n; len++)
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;
                dp[i][j] = inf;
                for (int k = opt[i][j - 1]; k <= min(j - 1, opt[i + 1][j]); k++) {
                    int val = dp[i][k] + dp[k + 1][j] + cost(i, j);
                    if (val < dp[i][j]) dp[i][j] = val, opt[i][j] = k;
                }
            }
    }

    int answer() { return n <= 1 ? 0 : dp[0][n - 1]; }
};
