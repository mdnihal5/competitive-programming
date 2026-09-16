// Author : md_nihal
// Source/adapted-from: KACTL graph/HLD.h pattern (single DFS for sizes/heavy child, second pass
// assigns positions, process() walks chains via a callback) -- reworked to explicit-stack DFS,
// and root is a constructor parameter rather than hardcoded to 0 (KACTL hardcodes root=0, which
// is an easy silent bug source if pasted into a 1-indexed problem).
// Deliberately does NOT embed a segment tree: process(u, v, op) hands you contiguous pos[]
// ranges and you call whatever segment tree you've separately pasted from inside op.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct HLD {
    int n, root;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, headOf, pos, subSize;

    HLD(int _n, int _root = 0) : n(_n), root(_root), adj(_n), parent(_n, -1),
        depth(_n, 0), heavy(_n, -1), headOf(_n), pos(_n), subSize(_n, 1) {}

    void addEdge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    void build() {
        vector<int> order;
        vector<bool> vis(n, false);
        vector<int> stk = {root};
        vis[root] = true;
        while (!stk.empty()) {
            int u = stk.back(); stk.pop_back();
            order.push_back(u);
            for (int v : adj[u])
                if (!vis[v]) {
                    vis[v] = true;
                    parent[v] = u;
                    depth[v] = depth[u] + 1;
                    stk.push_back(v);
                }
        }
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i], best = -1;
            for (int v : adj[u])
                if (v != parent[u]) {
                    subSize[u] += subSize[v];
                    if (best == -1 || subSize[v] > subSize[best]) best = v;
                }
            heavy[u] = best;
        }

        int timer = 0;
        vector<pair<int, int>> stk2 = {{root, root}};   // (node, chain head)
        while (!stk2.empty()) {
            auto [u, h] = stk2.back(); stk2.pop_back();
            headOf[u] = h;
            pos[u] = timer++;
            for (int v : adj[u])
                if (v != parent[u] && v != heavy[u])
                    stk2.push_back({v, v});               // starts a new chain
            if (heavy[u] != -1)
                stk2.push_back({heavy[u], h});             // pushed last -> popped first -> keeps
        }                                                  // the heavy chain's pos[] contiguous
    }

    int lca(int u, int v) {
        while (headOf[u] != headOf[v]) {
            if (depth[headOf[u]] < depth[headOf[v]]) swap(u, v);
            u = parent[headOf[u]];
        }
        return depth[u] < depth[v] ? u : v;
    }

    // Walks the u..v path chain by chain; op(l, r) gets a 0-indexed inclusive pos[] range
    // per chain segment (not guaranteed to be in u->v order -- reorder inside op if you need
    // a directed/non-commutative combine).
    void process(int u, int v, function<void(int, int)> op) {
        while (headOf[u] != headOf[v]) {
            if (depth[headOf[u]] < depth[headOf[v]]) swap(u, v);
            op(pos[headOf[u]], pos[u]);
            u = parent[headOf[u]];
        }
        if (pos[u] > pos[v]) swap(u, v);
        op(pos[u], pos[v]);
    }
};
/* Usage:
 *   HLD hld(n, root);
 *   hld.addEdge(u, v);          // repeat for every tree edge
 *   hld.build();
 *   hld.lca(u, v);
 *   hld.process(u, v, [&](int l, int r) { result = combine(result, segtree.query(l, r)); });
 *   // point update at node u: segtree.update(hld.pos[u], newVal);
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
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
#endif
