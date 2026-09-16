// Author : md_nihal
// Source/adapted-from: this repo's own Trees/weighted_lca.cpp, cleaned up and iterativized.
// Kept separate from Graphs/BinaryLifting.cpp on purpose: that struct's dist() only counts
// edge count (unweighted). This one accumulates edge weights along the binary-lifting jumps,
// which is a genuinely different query (weighted path distance), not just a style variant.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct WeightedLCA {
    int n, lg;
    vector<int> depth;
    vector<vector<pair<int, int>>> adj;   // (neighbour, edge weight)
    vector<vector<int>> up;
    vector<vector<int>> distUp;           // distUp[i][v] = weighted dist from v to up[i][v]

    WeightedLCA(int _n) : n(_n) {
        lg = 1;
        while ((1 << lg) < max(n, (int)2)) lg++;
        depth.assign(n, 0);
        adj.assign(n, {});
        up.assign(lg, vector<int>(n, -1));
        distUp.assign(lg, vector<int>(n, 0));
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void init(int root = 0) {
        dfs(root);
        for (int i = 1; i < lg; i++)
            for (int j = 0; j < n; j++) {
                int mid = up[i - 1][j];
                up[i][j] = mid == -1 ? -1 : up[i - 1][mid];
                distUp[i][j] = mid == -1 ? 0 : distUp[i - 1][j] + distUp[i - 1][mid];
            }
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

    // sum of edge weights on the path u..v
    int dist(int u, int v) {
        int l = lca(u, v);
        return distToAnc(u, l) + distToAnc(v, l);
    }

  private:
    // weighted distance from v up to its ancestor anc (anc must actually be an ancestor of v)
    int distToAnc(int v, int anc) {
        int res = 0;
        for (int i = lg - 1; i >= 0; i--)
            if (up[i][v] != -1 && depth[up[i][v]] >= depth[anc]) {
                res += distUp[i][v];
                v = up[i][v];
            }
        return res;
    }

    void dfs(int root) {
        // iterative: avoids recursion-depth blowups on path-shaped trees (n up to 2e5+)
        vector<int> stk = {root};
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            for (auto [v, w] : adj[u])
                if (v != up[0][u]) {
                    depth[v] = depth[u] + 1;
                    up[0][v] = u;
                    distUp[0][v] = w;
                    stk.push_back(v);
                }
        }
    }
};
/* Usage:
 *   WeightedLCA wl(n);
 *   wl.addEdge(u, v, w);        // repeat for every edge
 *   wl.init(root);
 *   wl.lca(u, v); wl.dist(u, v);   // dist = sum of edge weights on the u..v path
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    // Star graph, center 0, weights = child index * 10.
    {
        int n = 6;
        WeightedLCA wl(n);
        for (int i = 1; i < n; i++) wl.addEdge(0, i, i * 10);
        wl.init(0);
        assert(wl.lca(1, 5) == 0);
        assert(wl.dist(1, 5) == 10 + 50);
        assert(wl.dist(3, 3) == 0);
        cout << "star graph OK\n";
    }
    // Path 0-1-2-3-4 with weights 1,2,3,4 -> dist(0,4) must be the full sum.
    {
        int n = 5;
        WeightedLCA wl(n);
        int w[4] = {1, 2, 3, 4};
        for (int i = 0; i + 1 < n; i++) wl.addEdge(i, i + 1, w[i]);
        wl.init(0);
        assert(wl.dist(0, 4) == 1 + 2 + 3 + 4);
        assert(wl.dist(1, 3) == 2 + 3);
        assert(wl.lca(2, 4) == 2);
        cout << "path graph OK\n";
    }
    // Branching tree cross-checked against brute-force DFS distances + naive ancestor-set LCA.
    {
        mt19937 rng(777);
        int n = 150;
        WeightedLCA wl(n);
        vector<vector<pair<int, int>>> radj(n);
        vector<int> par(n, -1), rdepth(n, 0), distRoot(n, 0);
        for (int i = 1; i < n; i++) {
            int p = rng() % i, w = 1 + rng() % 100;
            wl.addEdge(p, i, w);
            radj[p].push_back({i, w}); radj[i].push_back({p, w});
        }
        wl.init(0);
        // brute force via BFS from root
        vector<bool> vis(n, false);
        vector<int> stk = {0};
        vis[0] = true;
        while (!stk.empty()) {
            int u = stk.back(); stk.pop_back();
            for (auto [v, w] : radj[u]) if (!vis[v]) {
                vis[v] = true; par[v] = u; rdepth[v] = rdepth[u] + 1;
                distRoot[v] = distRoot[u] + w; stk.push_back(v);
            }
        }
        for (int t = 0; t < 500; t++) {
            int u = rng() % n, v = rng() % n;
            vector<int> anc;
            int x = u;
            while (x != -1) { anc.push_back(x); x = par[x]; }
            x = v;
            while (find(all(anc), x) == anc.end()) x = par[x];
            int expectLca = x;
            int expectDist = distRoot[u] + distRoot[v] - 2 * distRoot[expectLca];
            assert(wl.lca(u, v) == expectLca);
            assert(wl.dist(u, v) == expectDist);
        }
        cout << "random tree vs brute force OK\n";
    }
    cout << "ALL WeightedLCA TESTS PASSED\n";
}
#endif
