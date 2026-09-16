// Author : md_nihal
// Source/adapted-from: standard persistent segment tree (versioned roots)
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
template<typename T, typename F>
struct PersistentSegTree {
    struct Node { T val; int l, r; };
    vector<Node> tree;
    vector<int> roots; // roots[v] = root node id of version v
    int n;
    T id;
    F combine;

    PersistentSegTree(const vector<T> &a, T id, F combine) : n(a.size()), id(id), combine(combine) {
        roots.push_back(build(a, 0, n - 1));
    }
    int build(const vector<T> &a, int l, int r) {
        if (l == r) { tree.push_back({a[l], -1, -1}); return (int)tree.size() - 1; }
        int m = (l + r) / 2;
        int lc = build(a, l, m), rc = build(a, m + 1, r);
        tree.push_back({combine(tree[lc].val, tree[rc].val), lc, rc});
        return (int)tree.size() - 1;
    }
    int update_(int node, int l, int r, int idx, T val) {
        if (l == r) { tree.push_back({val, -1, -1}); return (int)tree.size() - 1; }
        int m = (l + r) / 2;
        int lc = tree[node].l, rc = tree[node].r;
        if (idx <= m) lc = update_(lc, l, m, idx, val);
        else rc = update_(rc, m + 1, r, idx, val);
        tree.push_back({combine(tree[lc].val, tree[rc].val), lc, rc});
        return (int)tree.size() - 1;
    }
    int update(int version, int idx, T val) { // creates a NEW version, returns its id
        roots.push_back(update_(roots[version], 0, n - 1, idx, val));
        return (int)roots.size() - 1;
    }
    T query_(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return id;
        if (ql <= l && r <= qr) return tree[node].val;
        int m = (l + r) / 2;
        return combine(query_(tree[node].l, l, m, ql, qr), query_(tree[node].r, m + 1, r, ql, qr));
    }
    T query(int version, int l, int r) { return query_(roots[version], 0, n - 1, l, r); }
};
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    mt19937 rng(3434);
    int n = 12;
    vector<int> base(n);
    for (auto &x : base) x = rng() % 20;

    PersistentSegTree st(base, 0LL, [](int x, int y) { return x + y; });
    vector<vector<int>> versions = {base};

    for (int iter = 0; iter < 300; iter++) {
        int fromVer = rng() % versions.size();
        int idx = rng() % n, val = rng() % 20;
        st.update(fromVer, idx, val);
        vector<int> nv = versions[fromVer];
        nv[idx] = val;
        versions.push_back(nv);
    }

    for (size_t v = 0; v < versions.size(); v++) {
        int l = rng() % n, r = rng() % n; if (l > r) swap(l, r);
        int expect = 0; for (int i = l; i <= r; i++) expect += versions[v][i];
        assert(st.query((int)v, l, r) == expect);
    }
    cout << "OK\n";
}
#endif
