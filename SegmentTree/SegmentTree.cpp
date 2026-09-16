// Author : md_nihal
// Source/adapted-from: existing repo, rewritten iterative (bottom-up)
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
template<typename T, typename F>
struct SegTree {
    int n;
    vector<T> t;
    T id;
    F combine;
    SegTree(const vector<T> &a, T id, F combine) : n(a.size()), t(2 * n, id), id(id), combine(combine) {
        for (int i = 0; i < n; i++) t[i + n] = a[i];
        for (int i = n - 1; i > 0; i--) t[i] = combine(t[2 * i], t[2 * i + 1]);
    }
    void update(int i, T val) {
        for (t[i += n] = val; i > 1; i >>= 1) t[i >> 1] = combine(t[i], t[i ^ 1]);
    }
    T query(int l, int r) { // [l, r] inclusive, 0-indexed
        T resl = id, resr = id;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = combine(resl, t[l++]);
            if (r & 1) resr = combine(t[--r], resr);
        }
        return combine(resl, resr);
    }
};
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    mt19937 rng(1313);
    int n = 30;
    vector<int> a(n);
    for (auto &x : a) x = rng() % 100;

    SegTree st_sum(a, 0LL, [](int x, int y) { return x + y; });
    SegTree st_min(a, (long long)INT_MAX, [](int x, int y) { return min(x, y); });

    for (int iter = 0; iter < 3000; iter++) {
        if (rng() % 3 == 0) {
            int idx = rng() % n, val = rng() % 100;
            a[idx] = val;
            st_sum.update(idx, val);
            st_min.update(idx, val);
        } else {
            int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
            int esum = 0, emin = INT_MAX;
            for (int i = l; i <= r; i++) { esum += a[i]; emin = min(emin, a[i]); }
            assert(st_sum.query(l, r) == esum);
            assert(st_min.query(l, r) == emin);
        }
    }
    cout << "OK\n";
}
#endif
