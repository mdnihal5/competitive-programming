// Author : md_nihal
// Source/adapted-from: KACTL graph/BiconnectedComponents.h pattern -- tracks the EDGE id used
// to reach a node, not the parent NODE, which is what correctly handles multi-edges (two nodes
// joined by more than one direct edge). Skipping "the edge back to parent" by comparing node ids
// instead of edge ids is the classic bug: it silently treats both parallel edges as "going back
// to parent" and reports a bridge that doesn't actually exist.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct BridgesArticulation {
    int n, timer = 0, edgeCount = 0;
    vector<vector<pair<int, int>>> adj;   // (neighbour, edge id)
    vector<int> disc, low;
    vector<bool> isArt;
    vector<pair<int, int>> bridges;

    BridgesArticulation(int _n) : n(_n), adj(_n), disc(_n, -1), low(_n, 0), isArt(_n, false) {}

    void addEdge(int u, int v) {
        int id = edgeCount++;
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }

    void run() {
        for (int i = 0; i < n; i++)
            if (disc[i] == -1) dfs(i);
    }

  private:
    struct Frame { int u, parentEdge, idx, children; };

    void dfs(int start) {
        vector<Frame> stk = {{start, -1, 0, 0}};
        disc[start] = low[start] = timer++;

        while (!stk.empty()) {
            int top = (int)stk.size() - 1;
            int u = stk[top].u, parentEdge = stk[top].parentEdge, idx = stk[top].idx;

            if (idx < (int)adj[u].size()) {
                auto [v, eid] = adj[u][idx];
                stk[top].idx = idx + 1;                 // write back before any push/pop below
                if (eid == parentEdge) continue;         // skip only THIS edge back, not the node
                if (disc[v] == -1) {
                    disc[v] = low[v] = timer++;
                    stk[top].children++;
                    stk.push_back({v, eid, 0, 0});
                } else {
                    low[u] = min(low[u], disc[v]);
                }
            } else {
                int uLow = low[u], uChildren = stk[top].children;
                stk.pop_back();
                if (!stk.empty()) {
                    int p = stk.back().u;
                    low[p] = min(low[p], uLow);
                    if (uLow > disc[p]) bridges.push_back({p, u});
                    if (stk.back().parentEdge != -1 && uLow >= disc[p]) isArt[p] = true;
                } else if (uChildren > 1) {
                    isArt[u] = true;   // root of this DFS tree is an articulation point iff >1 child
                }
            }
        }
    }
};
/* Usage:
 *   BridgesArticulation ba(n);
 *   ba.addEdge(u, v);           // undirected; repeat for every edge (parallel edges are fine)
 *   ba.run();
 *   ba.bridges       // vector<pair<int,int>> of bridge edges
 *   ba.isArt[v]      // true iff v is an articulation point
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    // Two triangles {0,1,2} and {3,4,5} joined by a single edge 2-3: that edge is the only
    // bridge, and both 2 and 3 are articulation points; nothing inside a triangle is.
    {
        BridgesArticulation ba(6);
        ba.addEdge(0, 1); ba.addEdge(1, 2); ba.addEdge(2, 0);
        ba.addEdge(2, 3);
        ba.addEdge(3, 4); ba.addEdge(4, 5); ba.addEdge(5, 3);
        ba.run();
        assert(ba.bridges.size() == 1);
        auto [bu, bv] = ba.bridges[0];
        assert((bu == 2 && bv == 3) || (bu == 3 && bv == 2));
        assert(ba.isArt[2] && ba.isArt[3]);
        assert(!ba.isArt[0] && !ba.isArt[1] && !ba.isArt[4] && !ba.isArt[5]);
        cout << "two triangles + bridge OK\n";
    }
    // THE gotcha: 0=1 joined by two parallel edges, then 1-2 a single edge.
    // Naive "skip by parent node" would wrongly call the 0-1 tree edge a bridge.
    {
        BridgesArticulation ba(3);
        ba.addEdge(0, 1);   // tree edge
        ba.addEdge(0, 1);   // parallel edge -- must neutralize the tree edge as a bridge
        ba.addEdge(1, 2);
        ba.run();
        assert(ba.bridges.size() == 1);
        auto [bu, bv] = ba.bridges[0];
        assert((bu == 1 && bv == 2) || (bu == 2 && bv == 1));
        assert(ba.isArt[1] && !ba.isArt[0] && !ba.isArt[2]);
        cout << "parallel-edge gotcha OK\n";
    }
    // Deep chain: every edge is a bridge, every internal node is an articulation point.
    // Also the reason this DFS is iterative, not recursive.
    {
        int n = 200000;
        BridgesArticulation ba(n);
        for (int i = 0; i + 1 < n; i++) ba.addEdge(i, i + 1);
        ba.run();
        assert((int)ba.bridges.size() == n - 1);
        for (int i = 1; i + 1 < n; i++) assert(ba.isArt[i]);
        assert(!ba.isArt[0] && !ba.isArt[n - 1]);
        cout << "deep chain (n=200000) OK -- no stack overflow\n";
    }
    cout << "ALL BridgesArticulation TESTS PASSED\n";
}
#endif
