// HLD: 0-indexed tree rooted at root, O(n) build, O(log n) lca, O(log n) chains per path.
// pos[] is a DFS preorder: subtree of u = [pos[u], pos[u] + subSize[u] - 1]. process() gives each chain
// as an inclusive pos range, NOT in u->v order (reorder inside op for non-commutative merges).
// Usage: hld.addEdge(u, v); hld.build(); hld.lca(u, v); hld.process(u, v, [&](int l, int r) {...});
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Graphs/HLD.cpp"
/* Usage:
 *   HLD hld(n, root);
 *   hld.addEdge(u, v);          // repeat for every tree edge
 *   hld.build();
 *   hld.lca(u, v);
 *   hld.process(u, v, [&](int l, int r) { result = combine(result, segtree.query(l, r)); });
 *   // point update at node u: segtree.update(hld.pos[u], newVal);
 */

int32_t main() {
    {
        mt19937 rng(6);
        int n = 200000;
        HLD h(n);
        for (int i = 1; i < n; i++) h.addEdge(i - 1, i);
        h.build();
        assert(h.lca(n - 1, n / 2) == n / 2);
        for (int i = 0; i < 300; i++) {
            int m = 1 + rng() % 40;
            HLD t(m);
            for (int v = 1; v < m; v++) t.addEdge(rng() % v, v);
            t.build();
            for (int u = 0; u < m; u++) {
                set<int> sub;
                function<void(int)> go = [&](int x) { sub.insert(t.pos[x]); for (int y : t.adj[x]) if (y != t.parent[x]) go(y); };
                go(u);
                assert(*sub.begin() == t.pos[u] && (int)sub.size() == t.subSize[u] && *sub.rbegin() == t.pos[u] + t.subSize[u] - 1);
            }
        }
    }
    mt19937 rng(4242);
    for (int trial = 0; trial < 30; trial++) {
        int n = 20 + rng() % 400;
        HLD hld(n, 0);
        vector<vector<int>> radj(n);
        for (int i = 1; i < n; i++) {
            int p = rng() % i;
            hld.addEdge(p, i);
            radj[p].push_back(i); radj[i].push_back(p);
        }
        hld.build();

        // global structural invariant: pos[] must be a permutation of 0..n-1
        vector<bool> seen(n, false);
        for (int v = 0; v < n; v++) { assert(!seen[hld.pos[v]]); seen[hld.pos[v]] = true; }

        // independent brute-force parent/depth via BFS from root=0
        vector<int> bpar(n, -1), bdep(n, 0);
        vector<bool> vis(n, false);
        vector<int> stk = {0};
        vis[0] = true;
        while (!stk.empty()) {
            int u = stk.back(); stk.pop_back();
            for (int v : radj[u]) if (!vis[v]) { vis[v] = true; bpar[v] = u; bdep[v] = bdep[u] + 1; stk.push_back(v); }
        }

        for (int t = 0; t < 40; t++) {
            int u = rng() % n, v = rng() % n;

            // brute LCA via ancestor set
            vector<int> anc;
            int x = u;
            while (x != -1) { anc.push_back(x); x = bpar[x]; }
            x = v;
            while (find(all(anc), x) == anc.end()) x = bpar[x];
            int bruteLca = x;
            assert(hld.lca(u, v) == bruteLca);

            // brute node-set on the u..v path
            set<int> expectedPos;
            x = u;
            while (x != bruteLca) { expectedPos.insert(hld.pos[x]); x = bpar[x]; }
            x = v;
            while (x != bruteLca) { expectedPos.insert(hld.pos[x]); x = bpar[x]; }
            expectedPos.insert(hld.pos[bruteLca]);

            set<int> gotPos;
            hld.process(u, v, [&](int l, int r) { for (int p = l; p <= r; p++) gotPos.insert(p); });
            assert(gotPos == expectedPos);
        }
    }
    cout << "ALL HLD TESTS PASSED (30 random trees x 40 queries each)\n";
}
