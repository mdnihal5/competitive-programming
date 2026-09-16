// Author : md_nihal
// Source/adapted-from: existing repo, restyled
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct LazySegTree {
    struct Node { int mn = 0, mx = 0, sum = 0, lazy = 0; bool has_lazy = false; };
    int n;
    vector<Node> t;
    LazySegTree(int n) : n(n), t(4 * n + 5) {} // 1-indexed, range [1, n]

    void apply(int p, int l, int r, int v) {
        t[p].mn += v; t[p].mx += v; t[p].sum += v * (r - l + 1);
        if (t[p].has_lazy) t[p].lazy += v;
        else { t[p].lazy = v; t[p].has_lazy = true; }
    }
    void push(int p, int l, int r) {
        if (!t[p].has_lazy || l == r) return;
        int m = (l + r) >> 1;
        apply(p << 1, l, m, t[p].lazy);
        apply(p << 1 | 1, m + 1, r, t[p].lazy);
        t[p].lazy = 0; t[p].has_lazy = false;
    }
    void pull(int p) {
        t[p].mn = min(t[p << 1].mn, t[p << 1 | 1].mn);
        t[p].mx = max(t[p << 1].mx, t[p << 1 | 1].mx);
        t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
    }
    void range_add(int p, int l, int r, int L, int R, int v) {
        if (R < l || r < L) return;
        if (L <= l && r <= R) { apply(p, l, r, v); return; }
        push(p, l, r);
        int m = (l + r) >> 1;
        range_add(p << 1, l, m, L, R, v);
        range_add(p << 1 | 1, m + 1, r, L, R, v);
        pull(p);
    }
    Node query(int p, int l, int r, int L, int R) {
        if (R < l || r < L) return {inf, -inf, 0, 0, false};
        if (L <= l && r <= R) return t[p];
        push(p, l, r);
        int m = (l + r) >> 1;
        Node a = query(p << 1, l, m, L, R), b = query(p << 1 | 1, m + 1, r, L, R);
        return {min(a.mn, b.mn), max(a.mx, b.mx), a.sum + b.sum, 0, false};
    }
    void Add(int L, int R, int v) { range_add(1, 1, n, L, R, v); }
    int Min(int L, int R) { return query(1, 1, n, L, R).mn; }
    int Max(int L, int R) { return query(1, 1, n, L, R).mx; }
    int Sum(int L, int R) { return query(1, 1, n, L, R).sum; }
};
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    mt19937 rng(2323);
    int n = 20;
    LazySegTree st(n);
    vector<int> a(n + 1, 0);
    for (int iter = 0; iter < 3000; iter++) {
        int l = rng() % n + 1, r = rng() % n + 1; if (l > r) swap(l, r);
        if (rng() % 2 == 0) {
            int v = (int)(rng() % 21) - 10;
            st.Add(l, r, v);
            for (int i = l; i <= r; i++) a[i] += v;
        } else {
            int esum = 0, emn = INT_MAX, emx = INT_MIN;
            for (int i = l; i <= r; i++) { esum += a[i]; emn = min(emn, a[i]); emx = max(emx, a[i]); }
            assert(st.Sum(l, r) == esum);
            assert(st.Min(l, r) == emn);
            assert(st.Max(l, r) == emx);
        }
    }
    cout << "OK\n";
}
#endif
