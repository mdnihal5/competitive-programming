// Author : md_nihal
// Source/adapted-from: this repo's own Readme.md BinaryLift reference, cross-checked against KACTL graph/BinaryLifting.h
// Consolidates the old Graphs/LCA.cpp (free-function binary lifting) and Graphs/Kth_Ancestor.cpp
// (class-based kth ancestor) into one struct -- both did overlapping binary lifting separately.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct BinaryLift {
    int n, lg;
    vector<int> depth;
    vector<vector<int>> adj, up;

    BinaryLift(int _n) : n(_n) {
        lg = 1;
        while ((1 << lg) < max(n, (int)2)) lg++;
        depth.assign(n, 0);
        adj.assign(n, {});
        up.assign(lg, vector<int>(n, -1));
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // root = -1 processes every connected component (forest-safe); each
    // component gets an arbitrary root (the first unvisited index reached).
    void init(int root = -1) {
        if (root != -1) {
            dfs(root);
        } else {
            for (int u = 0; u < n; u++)
                if (up[0][u] == -1)
                    dfs(u);
        }
        for (int i = 1; i < lg; i++)
            for (int j = 0; j < n; j++)
                up[i][j] = up[i - 1][j] == -1 ? -1 : up[i - 1][up[i - 1][j]];
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int i = lg - 1; i >= 0; i--)
            if (depth[u] - (1 << i) >= depth[v])
                u = up[i][u];
        if (u == v) return u;
        for (int i = lg - 1; i >= 0; i--)
            if (up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        return up[0][u];
    }

    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    // -1 if u has fewer than k ancestors.
    int kthAncestor(int u, int k) {
        if (k > depth[u]) return -1;
        for (int i = 0; i < lg; i++)
            if (k >> i & 1) u = up[i][u];
        return u;
    }

  private:
    void dfs(int root) {
        // iterative to avoid recursion-depth blowups on path-shaped trees (n up to 2e5+)
        vector<int> stk = {root};
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            for (int v : adj[u])
                if (v != up[0][u]) {
                    depth[v] = depth[u] + 1;
                    up[0][v] = u;
                    stk.push_back(v);
                }
        }
    }
};
/* Usage:
 *   BinaryLift bl(n);
 *   bl.addEdge(u, v);           // repeat for every edge
 *   bl.init();                  // or init(root) for a single tree
 *   bl.lca(u, v); bl.dist(u, v); bl.kthAncestor(u, k);
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int naiveLca(vector<vector<int>> &adj, int n, int root, int u, int v) {
    vector<int> par(n, -1), dep(n, 0);
    vector<int> stk = {root};
    vector<bool> vis(n, false);
    vis[root] = true;
    while (!stk.empty()) {
        int x = stk.back(); stk.pop_back();
        for (int y : adj[x]) if (!vis[y]) { vis[y] = true; par[y] = x; dep[y] = dep[x] + 1; stk.push_back(y); }
    }
    vector<int> anc;
    int x = u;
    while (x != -1) { anc.push_back(x); x = par[x]; }
    x = v;
    while (find(all(anc), x) == anc.end()) x = par[x];
    return x;
}

int32_t main() {
    // Test 1: path graph 0-1-2-3-4-5-6 (stresses recursion-depth-sensitive dfs)
    {
        int n = 7;
        BinaryLift bl(n);
        vector<vector<int>> adj(n);
        for (int i = 0; i + 1 < n; i++) { bl.addEdge(i, i + 1); adj[i].push_back(i + 1); adj[i + 1].push_back(i); }
        bl.init(0);
        assert(bl.lca(0, 6) == 0);
        assert(bl.lca(3, 5) == 3);
        assert(bl.dist(0, 6) == 6);
        assert(bl.kthAncestor(6, 6) == 0);
        assert(bl.kthAncestor(6, 7) == -1);
        cout << "path graph OK\n";
    }
    // Test 2: star graph, center = 0
    {
        int n = 6;
        BinaryLift bl(n);
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; i++) { bl.addEdge(0, i); adj[0].push_back(i); adj[i].push_back(0); }
        bl.init(0);
        for (int i = 1; i < n; i++) for (int j = 1; j < n; j++) if (i != j)
            assert(bl.lca(i, j) == 0);
        assert(bl.kthAncestor(3, 1) == 0);
        cout << "star graph OK\n";
    }
    // Test 3: single node (n=1) -- the lg-computation edge case
    {
        BinaryLift bl(1);
        bl.init(0);
        assert(bl.lca(0, 0) == 0);
        assert(bl.dist(0, 0) == 0);
        cout << "n=1 OK\n";
    }
    // Test 4: random tree, cross-checked against a brute-force ancestor-set LCA
    {
        mt19937 rng(12345);
        int n = 200;
        BinaryLift bl(n);
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; i++) {
            int p = rng() % i;
            bl.addEdge(p, i);
            adj[p].push_back(i); adj[i].push_back(p);
        }
        bl.init(0);
        for (int t = 0; t < 500; t++) {
            int u = rng() % n, v = rng() % n;
            int expect = naiveLca(adj, n, 0, u, v);
            assert(bl.lca(u, v) == expect);
        }
        cout << "random tree vs brute force OK\n";
    }
    // Test 5: forest (two disconnected components), init(-1).
    // Component A: 0 is root (first unvisited index), children 1,2, and 1's child is 3.
    // Component B: edge 4-5, root defaults to 4 (first unvisited index reached after A).
    {
        int n = 6;
        BinaryLift bl(n);
        bl.addEdge(0, 1); bl.addEdge(0, 2); bl.addEdge(1, 3);
        bl.addEdge(4, 5);
        bl.init(-1);
        assert(bl.lca(2, 3) == 0);
        assert(bl.lca(1, 3) == 1);
        assert(bl.lca(4, 5) == 4);
        cout << "forest OK\n";
    }
    cout << "ALL BinaryLift TESTS PASSED\n";
}
#endif
