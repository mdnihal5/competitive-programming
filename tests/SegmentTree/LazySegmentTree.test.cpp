// LazySegTree st(n): 1-indexed [1, n], all zeros initially.
// Add(l, r, v) range add; Min/Max/Sum(l, r) range queries. All O(log n).
// Needs inf (1e18) from the prelude as the min/max identity.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/SegmentTree/LazySegmentTree.cpp"

int32_t main() {
    mt19937 rng(2323);
    for (int n = 1; n <= 30; n++) {
        LazySegTree st(n);
        vector<int> a(n + 1, 0);
        for (int iter = 0; iter < 300; iter++) {
            int l = rng() % n + 1, r = rng() % n + 1; if (l > r) swap(l, r);
            if (rng() % 2 == 0) {
                int v = (int)(rng() % 2001) - 1000;
                if (rng() % 10 == 0) v *= 1000000000;
                st.Add(l, r, v);
                for (int i = l; i <= r; i++) a[i] += v;
            } else {
                int esum = 0, emn = inf, emx = -inf;
                for (int i = l; i <= r; i++) { esum += a[i]; emn = min(emn, a[i]); emx = max(emx, a[i]); }
                assert(st.Sum(l, r) == esum);
                assert(st.Min(l, r) == emn);
                assert(st.Max(l, r) == emx);
            }
        }
    }
    cout << "OK\n";
}
