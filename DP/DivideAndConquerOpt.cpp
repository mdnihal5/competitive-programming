// Author : md_nihal
// Source/adapted-from: KACTL various/DivideAndConquerDP.h
// Applies when dp[i][j] = min over k<j of (dp[i-1][k] + C(k,j)), and the optimal
// split point opt(i,j) is monotone in j (opt(i,j) <= opt(i,j+1)) -- true whenever
// C satisfies the quadrangle inequality. Reduces one DP layer from O(n^2) to
// O(n log n). This file computes ONE layer; call it once per outer index i.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
// Fills cur[lo..hi) from prev, given cost(k, j) = transition cost from split k to j
// (k < j). Call solve(cur, prev, 0, n, 0, n-1) for the full row; it recurses to
// cover the whole [lo,hi) range while keeping the search window [optLo,optHi]
// monotonically shrinking.
template <class Cost>
void solveDnC(vector<int> &cur, const vector<int> &prev, int lo, int hi, int optLo, int optHi, Cost cost) {
    if (lo >= hi) return;
    int mid = (lo + hi) / 2;
    pair<int, int> best = {LLONG_MAX, -1};
    for (int k = optLo; k <= min(mid - 1, optHi); k++)
        best = min(best, {prev[k] + cost(k, mid), k});
    cur[mid] = best.first;
    int optMid = best.second;
    solveDnC(cur, prev, lo, mid, optLo, optMid, cost);
    solveDnC(cur, prev, mid + 1, hi, optMid, optHi, cost);
}
/* Usage:
 *   // dp[i][j] built from dp[i-1] one layer at a time:
 *   vector<int> prev = ..., cur(n, LLONG_MAX);
 *   auto cost = [&](int k, int j) { return C(k, j); };   // your transition cost
 *   solveDnC(cur, prev, 1, n, 0, n - 1, cost);            // cur[0] handled separately (base case)
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
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
#endif
