// Fenwick: 0-indexed point add, prefix/range sum, O(log n). lower_bound(v) = first index whose prefix
// sum >= v (n if none); only valid while all stored values are >= 0.
// Usage: f.update(i, v); f.query(l, r); f.lower_bound(v);
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/FenwickTree/FenwickTree.cpp"

int32_t main() {
    {
        Fenwick z(0);
        assert(z.lower_bound(1) == 0);
        Fenwick one(1);
        one.update(0, 3);
        assert(one.query(0, 0) == 3 && one.lower_bound(3) == 0 && one.lower_bound(4) == 1);
    }
    mt19937 rng0(8);
    for (int n = 1; n <= 40; n++) {
        Fenwick g(n);
        vector<int> a(n);
        for (int i = 0; i < n; i++) a[i] = rng0() % 4, g.update(i, a[i]);
        for (int v = -1; v <= 4 * n + 1; v++) {
            int e = n, s = 0;
            for (int i = 0; i < n; i++) { s += a[i]; if (s >= v) { e = i; break; } }
            assert(g.lower_bound(v) == e);
        }
    }
    mt19937 rng(12345);
    {
        Fenwick f(10);
        vector<int> a(10, 0);
        for (int iter = 0; iter < 2000; iter++) {
            int op = rng() % 2;
            if (op == 0) {
                int idx = rng() % 10, val = (int)(rng() % 21) - 10;
                f.update(idx, val); a[idx] += val;
            } else {
                int l = rng() % 10, r = rng() % 10; if (l > r) swap(l, r);
                int expect = 0; for (int i = l; i <= r; i++) expect += a[i];
                assert(f.query(l, r) == expect);
            }
        }
    }
    {
        int n = 12;
        Fenwick f(n);
        vector<int> a(n, 0);
        for (int i = 0; i < n; i++) { int v = rng() % 5; f.update(i, v); a[i] = v; }
        vector<int> pref(n + 1, 0);
        for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];
        for (int val = 0; val <= pref[n] + 2; val++) {
            int expect = n; // if never reached, brute returns n (no valid index)
            for (int i = 0; i < n; i++) if (pref[i + 1] >= val) { expect = i; break; }
            assert(f.lower_bound(val) == expect);
        }
    }
    cout << "OK\n";
}
