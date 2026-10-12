struct BitmaskDP {
    int n;
    vector<vector<int>> cost;
    vector<int> memo;

    BitmaskDP(vector<vector<int>> c) : n(c.size()), cost(move(c)), memo(1 << n, -1) {}

    int solve(int mask) {
        if (mask == (1 << n) - 1) return 0;
        if (memo[mask] != -1) return memo[mask];
        int worker = __builtin_popcountll(mask), best = inf;
        for (int task = 0; task < n; task++)
            if (!(mask >> task & 1)) best = min(best, cost[worker][task] + solve(mask | 1 << task));
        return memo[mask] = best;
    }

    int answer() { return solve(0); }
};
