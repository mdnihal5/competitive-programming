// ToggleSegTree st(n): 0-indexed binary array, all 0 initially.
// toggle(l, r) flips every bit in [l, r]; query(l, r) = number of ones in [l, r]. Both O(log n).
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/SegmentTree/RangeToggleSum.cpp"

// noinline wrappers: stops GCC inlining the recursion into main, which yields a false -Warray-bounds
__attribute__((noinline)) void doToggle(ToggleSegTree &st, int l, int r) { st.toggle(l, r); }
__attribute__((noinline)) int ones(ToggleSegTree &st, int l, int r) { return st.query(l, r); }

int32_t main() {
    mt19937 rng(9191);
    for (int tc = 0; tc < 60; tc++) {
        int n = 1 + rng() % 30;
        vector<int> a(n, 0);
        ToggleSegTree st(n);
        for (int iter = 0; iter < 200; iter++) {
            int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
            if (rng() % 2 == 0) {
                doToggle(st, l, r);
                for (int i = l; i <= r; i++) a[i] ^= 1;
            } else {
                int expect = 0; for (int i = l; i <= r; i++) expect += a[i];
                assert(ones(st, l, r) == expect);
            }
        }
    }
    cout << "OK\n";
}
