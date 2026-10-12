// SegTree<T,F> st(a, identity, combine): 0-indexed, query(l, r) inclusive, update(i, v) = point assign.
// combine must be associative; commutativity NOT required (order is preserved).
// Build O(n), update/query O(log n). Iterative bottom-up, any n >= 1.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/SegmentTree/SegmentTree.cpp"

int32_t main() {
    mt19937 rng(1313);
    for (int n = 1; n <= 40; n++) {
        vector<int> a(n);
        for (auto &x : a) x = rng() % 100;
        vector<string> s(n);
        for (auto &x : s) x = string(1, 'a' + rng() % 26);
        SegTree st_sum(a, 0LL, [](int x, int y) { return x + y; });
        SegTree st_min(a, inf, [](int x, int y) { return min(x, y); });
        SegTree st_cat(s, string(), [](string x, string y) { return x + y; });
        for (int iter = 0; iter < 300; iter++) {
            if (rng() % 3 == 0) {
                int idx = rng() % n, val = rng() % 100;
                a[idx] = val; s[idx] = string(1, 'a' + val % 26);
                st_sum.update(idx, val); st_min.update(idx, val); st_cat.update(idx, s[idx]);
            } else {
                int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
                int esum = 0, emin = inf; string ecat;
                for (int i = l; i <= r; i++) { esum += a[i]; emin = min(emin, a[i]); ecat += s[i]; }
                assert(st_sum.query(l, r) == esum);
                assert(st_min.query(l, r) == emin);
                assert(st_cat.query(l, r) == ecat);
            }
        }
    }
    cout << "OK\n";
}
