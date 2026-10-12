// solveDnC: one layer of dp[j] = min_{k<j}(prev[k] + cost(k, j)) when opt(j) is monotone in j
// (quadrangle inequality). O(n log n) per layer. 0-indexed, fills cur[lo..hi).
// Usage: solveDnC(cur, prev, 1, n, 0, n - 1, cost); cur[0] is the base case, handle it yourself.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/DP/DivideAndConquerOpt.cpp"
/* Usage:
 *   // dp[i][j] built from dp[i-1] one layer at a time:
 *   vector<int> prev = ..., cur(n, LLONG_MAX);
 *   auto cost = [&](int k, int j) { return C(k, j); };   // your transition cost
 *   solveDnC(cur, prev, 1, n, 0, n - 1, cost);            // cur[0] handled separately (base case)
 */

int32_t main() {
    mt19937 rng(3);
    for (int it = 0; it < 200; it++) {
        int m = 2 + rng() % 40;
        vector<int> p(m), c(m, LLONG_MAX), b(m, LLONG_MAX), w(m);
        for (auto &x : p) x = rng() % 50;
        for (auto &x : w) x = rng() % 10;
        for (int i = 1; i < m; i++) w[i] += w[i - 1];
        auto f = [&](int k, int j) { return (w[j] - w[k]) * (w[j] - w[k]); };
        solveDnC(c, p, 1, m, 0, m - 1, f);
        for (int j = 1; j < m; j++) for (int k = 0; k < j; k++) b[j] = min(b[j], p[k] + f(k, j));
        for (int j = 1; j < m; j++) assert(c[j] == b[j]);
    }
    // Toy check: partition points 0..n-1 into groups minimizing sum of squared
    // group sizes, one previous-layer transition. cost(k, j) = (j - k) * (j - k).
    int n = 10;
    vector<int> prev(n, 0);          // pretend layer 0: prev[k] = 0 for all k (single group ending at k)
    vector<int> cur(n, LLONG_MAX);
    auto cost = [](int k, int j) { return (j - k) * (j - k); };
    solveDnC(cur, prev, 1, n, 0, n - 1, cost);

    // brute force cross-check for the same layer
    vector<int> brute(n, LLONG_MAX);
    for (int j = 1; j < n; j++)
        for (int k = 0; k < j; k++)
            brute[j] = min(brute[j], prev[k] + cost(k, j));

    for (int j = 1; j < n; j++) assert(cur[j] == brute[j]);
    cout << "DivideAndConquerOpt OK\n";
}
