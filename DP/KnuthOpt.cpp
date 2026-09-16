// Author : md_nihal
// Source/adapted-from: KACTL various/KnuthDP.h
// Applies to interval DP dp[i][j] = min over i<=k<j of (dp[i][k] + dp[k+1][j]) + C(i,j),
// when C satisfies the quadrangle inequality (monotonicity + convexity) -- then the
// optimal split opt(i,j) is monotone: opt(i,j-1) <= opt(i,j) <= opt(i+1,j). This
// prunes the k-search window per cell, taking O(n^3) down to O(n^2). Classic
// example: optimal BST / matrix chain / "optimal merge with the quadrangle property".
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
template <class Cost>
struct KnuthOpt {
    int n;
    vector<vector<int>> dp, opt;
    Cost cost; // cost(i, j): the base cost added to dp[i][k]+dp[k+1][j] for interval [i,j]

    KnuthOpt(int n_, Cost cost_) : n(n_), dp(n, vector<int>(n, 0)), opt(n, vector<int>(n, 0)), cost(cost_) {
        for (int i = 0; i < n; i++) opt[i][i] = i;
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                dp[i][j] = LLONG_MAX;
                for (int k = opt[i][j - 1]; k <= min(j - 1, opt[i + 1][j]); k++) {
                    int val = dp[i][k] + (k + 1 <= j ? dp[k + 1][j] : 0) + cost(i, j);
                    if (val < dp[i][j]) { dp[i][j] = val; opt[i][j] = k; }
                }
            }
        }
    }

    int answer() { return n <= 1 ? 0 : dp[0][n - 1]; }
};
/* Usage:
 *   auto cost = [&](int i, int j) { return C(i, j); };   // your interval's base cost, quadrangle-inequality-satisfying
 *   KnuthOpt opt(n, cost);
 *   int best = opt.answer();
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
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
#endif
