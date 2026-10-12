struct DigitDP {
    string digits;
    int K;
    vector<vector<int>> memo;

    DigitDP(int bound, int k) : digits(to_string(bound)), K(k), memo(digits.size(), vector<int>(9 * digits.size() + 1, -1)) {}

    int solve(int pos, bool tight, int sum) {
        if (pos == (int)digits.size()) return sum <= K;
        if (!tight && memo[pos][sum] != -1) return memo[pos][sum];
        int limit = tight ? digits[pos] - '0' : 9, total = 0;
        for (int d = 0; d <= limit; d++) total += solve(pos + 1, tight && d == limit, sum + d);
        return tight ? total : memo[pos][sum] = total;
    }

    int count() { return solve(0, true, 0); }
};
