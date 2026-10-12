// KnuthOpt: dp[i][j] = min_{i<=k<j}(dp[i][k] + dp[k+1][j]) + cost(i, j), 0-indexed, O(n^2) memory+time.
// Needs cost to satisfy the quadrangle inequality (opt[i][j-1] <= opt[i][j] <= opt[i+1][j]).
// Usage: KnuthOpt opt(n, [&](int i, int j) { return ...; }); int best = opt.answer();
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/DP/KnuthOpt.cpp"
/* Usage:
 *   auto cost = [&](int i, int j) { return C(i, j); };   // your interval's base cost, quadrangle-inequality-satisfying
 *   KnuthOpt opt(n, cost);
 *   int best = opt.answer();
 */

static int bruteInterval(int n, function<int(int,int)> cost) {
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = LLONG_MAX;
            for (int k = i; k < j; k++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + cost(i, j));
        }
    }
    return n <= 1 ? 0 : dp[0][n - 1];
}

int32_t main() {
    mt19937 rng0(1);
    for (int it = 0; it < 200; it++) {
        int m = 1 + rng0() % 25;
        vector<int> pr(m + 1);
        for (int i = 0; i < m; i++) pr[i + 1] = pr[i] + 1 + rng0() % 20;
        auto f = [&](int i, int j) { return pr[j + 1] - pr[i]; };
        assert(KnuthOpt(m, f).answer() == bruteInterval(m, f));
    }
    int n = 12;
    // toy cost satisfying the quadrangle inequality: sum of a fixed weight array over [i,j]
    vector<int> w(n);
    mt19937 rng(7);
    for (int i = 0; i < n; i++) w[i] = 1 + (int)(rng() % 20);
    vector<int> pre(n + 1, 0);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + w[i];
    auto cost = [&](int i, int j) { return pre[j + 1] - pre[i]; }; // range-sum cost: standard quadrangle-satisfying example

    KnuthOpt opt(n, cost);
    int fast = opt.answer();
    int brute = bruteInterval(n, cost);
    assert(fast == brute);

    cout << "KnuthOpt OK\n";
}
