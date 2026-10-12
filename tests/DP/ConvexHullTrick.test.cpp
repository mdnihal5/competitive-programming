// LineContainer (KACTL): max of lines k*x+m at x; amortised O(log n) add/query. Needs lines >= 1
// (query on empty set is UB). For MIN: add(-k, -m), answer is -query(x).
// Usage: lc.add(k, m); lc.query(x);
#include "bits/stdc++.h"
using namespace std;
#define int long long
const int inf = 1E18;

#include "../../lib/DP/ConvexHullTrick.cpp"
/* Usage:
 *   LineContainer lc;
 *   lc.add(k, m);            // insert line y = k*x + m
 *   lc.query(x);              // max over all inserted lines at x
 *   // for MIN: lc.add(-k, -m), then -lc.query(x)
 */

int32_t main() {
    LineContainer lc;
    lc.add(2, 3);   // y = 2x + 3
    lc.add(-1, 10); // y = -x + 10
    // at x=0: max(3, 10) = 10 ; at x=10: max(23, 0) = 23
    assert(lc.query(0) == 10);
    assert(lc.query(10) == 23);

    // brute-force cross-check: random lines, random query points, vs naive max
    mt19937 rng(11);
    for (int iter = 0; iter < 300; iter++) {
        LineContainer fast;
        vector<pair<int, int>> lines;
        int m = 1 + rng() % 30;
        for (int i = 0; i < m; i++) {
            int k = (int)(rng() % 2001) - 1000;
            int mm = (int)(rng() % 2001) - 1000;
            fast.add(k, mm);
            lines.push_back({k, mm});
        }
        for (int q = 0; q < 20; q++) {
            int x = (int)(rng() % 201) - 100;
            int brute = LLONG_MIN;
            for (auto &[k, mm] : lines) brute = max(brute, k * x + mm);
            assert(fast.query(x) == brute);
        }
    }

    cout << "OK\n";
}
