// Author : md_nihal
// Source/adapted-from: existing repo (Graphs/UnionFind.cpp) -- consolidated two
// redundant classes into one; fixed a real bug: the old size-based DSU initialized
// from index 1, leaving node 0 (the overwhelmingly common starting index) broken.

#include "bits/stdc++.h"
using namespace std;
#define int long long

/* ---- SNIPPET START ---- */
struct DSU {
    vector<int> par, sz;

    DSU(int n) : par(n), sz(n, 1) { iota(par.begin(), par.end(), 0); }

    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }

    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
        return true;
    }

    bool connected(int x, int y) { return find(x) == find(y); }
    int compSize(int x) { return sz[find(x)]; }
};
/* Usage:
 *   DSU dsu(n);           // 0-indexed, n elements
 *   dsu.unite(u, v);
 *   dsu.connected(u, v);
 *   dsu.compSize(u);      // size of u's component
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    DSU dsu(5);
    assert(!dsu.connected(0, 1));
    dsu.unite(0, 1);
    assert(dsu.connected(0, 1) && dsu.compSize(0) == 2);
    dsu.unite(1, 2);
    assert(dsu.connected(0, 2) && dsu.compSize(2) == 3);
    assert(!dsu.connected(0, 3));
    assert(dsu.compSize(3) == 1);   // node 0 must work correctly -- the old bug's exact failure point
    assert(!dsu.unite(0, 2));       // already connected, unite is a no-op, returns false

    // brute-force cross-check: naive component-recompute vs. DSU, random union sequences
    mt19937 rng(7);
    for (int iter = 0; iter < 200; iter++) {
        int n = 2 + rng() % 15;
        DSU d(n);
        vector<vector<int>> edges;
        int ops = rng() % 20;
        for (int i = 0; i < ops; i++) {
            int u = rng() % n, v = rng() % n;
            d.unite(u, v);
            edges.push_back({u, v});
        }
        // brute force: BFS/union via repeated closure over edges
        vector<int> comp(n); iota(comp.begin(), comp.end(), 0);
        bool changed = true;
        while (changed) {
            changed = false;
            for (auto &e : edges) {
                int a = comp[e[0]], b = comp[e[1]];
                if (a != b) { for (auto &c : comp) if (c == b) c = a; changed = true; }
            }
        }
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                assert(d.connected(u, v) == (comp[u] == comp[v]));
    }

    cout << "OK\n";
}
#endif
