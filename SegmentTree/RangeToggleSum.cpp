// Author : md_nihal
// Source/adapted-from: existing repo (toggle_range_sum.cpp), restyled
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct ToggleSegTree { // binary array: range-flip (0<->1), range-sum
    int n;
    vector<int> st, lazy;
    ToggleSegTree(int n) : n(n), st(4 * n), lazy(4 * n) {}
    void apply_(int p, int l, int r) {
        st[p] = (r - l + 1) - st[p];
        lazy[p] ^= 1;
    }
    void push(int p, int l, int r) {
        if (!lazy[p] || l == r) return;
        int m = (l + r) >> 1;
        apply_(p << 1, l, m); apply_(p << 1 | 1, m + 1, r);
        lazy[p] = 0;
    }
    void upd(int p, int l, int r, int i, int j) {
        if (r < i || j < l) return;
        if (i <= l && r <= j) return apply_(p, l, r);
        push(p, l, r);
        int m = (l + r) >> 1;
        upd(p << 1, l, m, i, j); upd(p << 1 | 1, m + 1, r, i, j);
        st[p] = st[p << 1] + st[p << 1 | 1];
    }
    int qry(int p, int l, int r, int i, int j) {
        if (r < i || j < l) return 0;
        if (i <= l && r <= j) return st[p];
        push(p, l, r);
        int m = (l + r) >> 1;
        return qry(p << 1, l, m, i, j) + qry(p << 1 | 1, m + 1, r, i, j);
    }
    void toggle(int l, int r) { upd(1, 0, n - 1, l, r); }
    int query(int l, int r) { return qry(1, 0, n - 1, l, r); }
};
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    mt19937 rng(9191);
    int n = 20;
    vector<int> a(n, 0);
    ToggleSegTree st(n);
    for (int iter = 0; iter < 3000; iter++) {
        int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
        if (rng() % 2 == 0) {
            st.toggle(l, r);
            for (int i = l; i <= r; i++) a[i] ^= 1;
        } else {
            int expect = 0; for (int i = l; i <= r; i++) expect += a[i];
            assert(st.query(l, r) == expect);
        }
    }
    cout << "OK\n";
}
#endif
