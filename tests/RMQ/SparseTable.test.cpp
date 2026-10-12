// SparseTable<T,F> st(a, combine): 0-indexed, query(l, r) inclusive.
// combine must be associative AND idempotent (min/max/gcd/and/or), NOT sum.
// Build O(n log n) memory/time, query O(1).
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/RMQ/SparseTable.cpp"

int32_t main() {
    mt19937 rng(4242);
    for (int n = 1; n <= 70; n++) {
        vector<int> a(n);
        for (auto &x : a) x = rng() % 100;
        SparseTable st_min(a, [](int x, int y) { return min(x, y); });
        SparseTable st_max(a, [](int x, int y) { return max(x, y); });
        SparseTable st_gcd(a, [](int x, int y) { return __gcd(x, y); });
        for (int l = 0; l < n; l++) {
            int emin = a[l], emax = a[l], egcd = a[l];
            for (int r = l; r < n; r++) {
                emin = min(emin, a[r]); emax = max(emax, a[r]); egcd = __gcd(egcd, a[r]);
                assert(st_min.query(l, r) == emin);
                assert(st_max.query(l, r) == emax);
                assert(st_gcd.query(l, r) == egcd);
            }
        }
    }
    vector<pair<int, int>> p = {{3, 0}, {1, 1}, {1, 2}, {5, 3}};
    SparseTable sp(p, [](pair<int, int> x, pair<int, int> y) { return min(x, y); });
    assert(sp.query(0, 3) == make_pair(1LL, 1LL));
    cout << "OK\n";
}
