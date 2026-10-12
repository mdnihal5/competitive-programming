// BitmaskDP: assignment problem, cost[worker][task] (square), O(2^n * n). Edit solve() for other
// bitmask problems (worker = popcount(mask) trick).
// Usage: BitmaskDP dp(cost); int best = dp.answer();
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/DP/BitmaskDP.cpp"
/* Usage:
 *   BitmaskDP dp(costMatrix);      // costMatrix[worker][task]
 *   int minCost = dp.answer();
 */

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
    mt19937 rng(5);
    for (int it = 0; it < 200; it++) {
        int n = 1 + rng() % 7;
        vector<vector<int>> c(n, vector<int>(n));
        for (auto &r : c) for (auto &x : r) x = rng() % 100;
        assert(BitmaskDP(c).answer() == bruteAssignment(c));
    }
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
