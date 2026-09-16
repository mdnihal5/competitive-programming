// Author : md_nihal
// Pattern reference, not a fixed library: cp-algorithms.com/dynamic_programming/profile-dynamics.html
// and the standard assignment-problem bitmask-DP shape (AtCoder EDU DP contest,
// problem O). Toy example: N workers, N tasks, cost[worker][task] -- minimum cost
// to assign every task to a distinct worker. Lines marked // CHANGE THIS: are the
// problem-specific parts.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct BitmaskDP {
    int n;
    vector<vector<int>> cost;         // CHANGE THIS: your problem's per-item cost/value table
    vector<int> memo;                 // memo[mask] = best cost to assign tasks in `mask`

    BitmaskDP(vector<vector<int>> c) : n((int)c.size()), cost(move(c)), memo(1 << n, -1) {}

    // solve(mask) = min cost to have assigned exactly the tasks set in `mask`,
    // using workers 0..popcount(mask)-1 in order (the next worker is always
    // popcount(mask), a standard trick that avoids a separate "worker index" state)
    int solve(int mask) {
        if (mask == (1 << n) - 1) return 0;                      // CHANGE THIS: base case
        if (memo[mask] != -1) return memo[mask];

        int worker = __builtin_popcount(mask);
        int best = inf;
        for (int task = 0; task < n; task++) {
            if (mask & (1 << task)) continue;                    // CHANGE THIS: transition + pruning
            best = min(best, cost[worker][task] + solve(mask | (1 << task)));
        }
        return memo[mask] = best;
    }

    int answer() { return solve(0); }
};
/* Usage:
 *   BitmaskDP dp(costMatrix);      // costMatrix[worker][task]
 *   int minCost = dp.answer();
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
static int bruteAssignment(const vector<vector<int>> &cost) {
    int n = (int)cost.size();
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    int best = INT_MAX;
    do {
        int total = 0;
        for (int w = 0; w < n; w++) total += cost[w][perm[w]];
        best = min(best, total);
    } while (next_permutation(perm.begin(), perm.end()));
    return best;
}

int32_t main() {
    vector<vector<int>> cost = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };
    BitmaskDP dp(cost);
    int fast = dp.answer();
    int brute = bruteAssignment(cost);
    assert(fast == brute);
    cout << "BitmaskDP OK (min assignment cost = " << fast << ")\n";
}
#endif
