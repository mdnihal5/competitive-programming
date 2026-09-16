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
struct MaxSubarraySegTree {
    struct Node { int pref, suf, val, sum; };
    int n, neutral;
    vector<Node> t;
    MaxSubarraySegTree(int n, int assign_value) : n(n), neutral(assign_value), t(4 * n) {
        build(1, 0, n - 1);
    }
    void build(int i, int l, int r) {
        if (l == r) { t[i] = {neutral, neutral, neutral, neutral}; return; }
        int mid = (l + r) >> 1;
        build(2 * i, l, mid); build(2 * i + 1, mid + 1, r);
        t[i] = merge(t[2 * i], t[2 * i + 1]);
    }
    Node merge(Node a, Node b) {
        Node c;
        c.pref = max(a.pref, a.sum + b.pref);
        c.suf = max(b.suf, b.sum + a.suf);
        c.val = max({a.val, b.val, a.suf + b.pref});
        c.sum = a.sum + b.sum;
        return c;
    }
    void modify_(int i, int l, int r, int pos, int val) {
        if (l > pos || r < pos) return;
        if (l == pos && r == pos) { t[i] = {val, val, val, val}; return; }
        int mid = (l + r) >> 1;
        modify_(2 * i, l, mid, pos, val); modify_(2 * i + 1, mid + 1, r, pos, val);
        t[i] = merge(t[2 * i], t[2 * i + 1]);
    }
    static constexpr int NEG_INF = -(int)4e18;
    Node query_(int i, int l, int r, int tl, int tr) {
        if (l > tr || r < tl) return {NEG_INF, NEG_INF, NEG_INF, 0}; // identity: contributes nothing to any of pref/suf/val, sum=0
        if (l >= tl && r <= tr) return t[i];
        int mid = (l + r) >> 1;
        return merge(query_(2 * i, l, mid, tl, tr), query_(2 * i + 1, mid + 1, r, tl, tr));
    }
    void modify(int pos, int val) { modify_(1, 0, n - 1, pos, val); }
    int query(int l, int r) { return query_(1, 0, n - 1, l, r).val; } // max subarray sum in [l, r]
};
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    mt19937 rng(8989);
    int n = 20;
    vector<int> a(n, -1000000000000LL);
    MaxSubarraySegTree st(n, -1000000000000LL);
    for (int i = 0; i < n; i++) { int v = (int)(rng() % 21) - 10; a[i] = v; st.modify(i, v); }

    for (int iter = 0; iter < 500; iter++) {
        if (rng() % 3 == 0) {
            int idx = rng() % n, v = (int)(rng() % 21) - 10;
            a[idx] = v; st.modify(idx, v);
        } else {
            int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
            int best = LLONG_MIN;
            for (int i = l; i <= r; i++) { int cur = 0; for (int j = i; j <= r; j++) { cur += a[j]; best = max(best, cur); } }
            assert(st.query(l, r) == best);
        }
    }
    cout << "OK\n";
}
#endif
