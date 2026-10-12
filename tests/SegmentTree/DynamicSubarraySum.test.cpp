// MaxSubarraySegTree st(a): 0-indexed, update(i, v) = point assign, query(l, r) = max NON-EMPTY subarray sum in [l, r].
// Values may be negative; |sum| should stay well below 1e18 (identity uses -inf).
// Build O(n), update/query O(log n). Iterative, any n >= 1.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/SegmentTree/DynamicSubarraySum.cpp"

int32_t main() {
    mt19937 rng(8989);
    for (int n = 1; n <= 30; n++) {
        for (int mag : {10LL, 1000000000000LL}) {
            vector<int> a(n);
            for (auto &x : a) x = (int)(rng() % (2 * mag + 1)) - mag;
            MaxSubarraySegTree st(a);
            for (int iter = 0; iter < 150; iter++) {
                if (rng() % 3 == 0) {
                    int idx = rng() % n, v = (int)(rng() % (2 * mag + 1)) - mag;
                    a[idx] = v; st.update(idx, v);
                } else {
                    int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
                    int best = -inf;
                    for (int i = l; i <= r; i++) { int cur = 0; for (int j = i; j <= r; j++) { cur += a[j]; best = max(best, cur); } }
                    assert(st.query(l, r) == best);
                }
            }
        }
    }
    cout << "OK\n";
}
