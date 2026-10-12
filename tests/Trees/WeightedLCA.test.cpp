// WeightedLCA wl(n); wl.addEdge(u, v, w) per edge (0-indexed, weights may be 0); wl.init(root) once.
// wl.lca(u, v), wl.dist(u, v) = sum of edge weights on the path. Binary lifting: O(n log n) build, O(log n) query.
// init is an iterative DFS, so 2e5-deep path trees are fine. Tree must be connected.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Trees/WeightedLCA.cpp"
/* Usage:
 *   WeightedLCA wl(n);
 *   wl.addEdge(u, v, w);        // repeat for every edge
 *   wl.init(root);
 *   wl.lca(u, v); wl.dist(u, v);   // dist = sum of edge weights on the u..v path
 */

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
    // n = 1, and a deep path rooted away from 0 (checks iterative init + non-zero root)
    {
        WeightedLCA one(1);
        one.init(0);
        assert(one.lca(0, 0) == 0 && one.dist(0, 0) == 0);
        int n = 200000;
        WeightedLCA wl(n);
        for (int i = 0; i + 1 < n; i++) wl.addEdge(i, i + 1, 3);
        wl.init(n / 2);
        assert(wl.lca(0, n - 1) == n / 2);
        assert(wl.dist(0, n - 1) == 3LL * (n - 1));
        assert(wl.lca(n - 1, n - 5) == n - 5);
        assert(wl.dist(10, 20) == 30);
    }
    // random trees with random roots and zero weights vs brute-force parent walk
    {
        mt19937 rng(99);
        for (int iter = 0; iter < 200; iter++) {
            int n = 1 + rng() % 30, root = rng() % n;
            vector<vector<pair<int, int>>> g(n);
            WeightedLCA wl(n);
            for (int i = 1; i < n; i++) {
                int p = rng() % i, w = rng() % 5;
                wl.addEdge(p, i, w); g[p].push_back({i, w}); g[i].push_back({p, w});
            }
            wl.init(root);
            vector<int> par(n, -1), dep(n, 0), dd(n, 0), st = {root};
            while (!st.empty()) {
                int u = st.back(); st.pop_back();
                for (auto [v, w] : g[u]) if (v != par[u]) { par[v] = u; dep[v] = dep[u] + 1; dd[v] = dd[u] + w; st.push_back(v); }
            }
            for (int u = 0; u < n; u++) for (int v = 0; v < n; v++) {
                int a = u, b = v;
                while (a != b) { if (dep[a] < dep[b]) swap(a, b); a = par[a]; }
                assert(wl.lca(u, v) == a);
                assert(wl.dist(u, v) == dd[u] + dd[v] - 2 * dd[a]);
            }
        }
    }
    cout << "ALL WeightedLCA TESTS PASSED\n";
}
