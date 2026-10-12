// BridgesArticulation: 0-indexed undirected graph, parallel edges ok, iterative DFS, O(n + m).
// After run(): bridges = list of (parent, child) pairs, isArt[v] = articulation point.
// Usage: ba.addEdge(u, v); ba.run();
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Graphs/BridgesArticulation.cpp"
/* Usage:
 *   BridgesArticulation ba(n);
 *   ba.addEdge(u, v);           // undirected; repeat for every edge (parallel edges are fine)
 *   ba.run();
 *   ba.bridges       // vector<pair<int,int>> of bridge edges
 *   ba.isArt[v]      // true iff v is an articulation point
 */

int32_t main() {
    {
        mt19937 rng(21);
        for (int iter = 0; iter < 500; iter++) {
            int n = 1 + rng() % 8, m = rng() % 12;
            vector<pair<int, int>> es;
            BridgesArticulation ba(n);
            for (int i = 0; i < m; i++) {
                int u = rng() % n, v = rng() % n;
                ba.addEdge(u, v), es.push_back({u, v});
            }
            ba.run();
            auto comps = [&](int skipEdge, int skipNode) {
                vector<int> p(n);
                iota(p.begin(), p.end(), 0);
                function<int(int)> find = [&](int x) { return p[x] == x ? x : p[x] = find(p[x]); };
                for (int i = 0; i < m; i++)
                    if (i != skipEdge && es[i].first != skipNode && es[i].second != skipNode) p[find(es[i].first)] = find(es[i].second);
                int c = 0;
                for (int v = 0; v < n; v++) if (v != skipNode && find(v) == v) c++;
                return c;
            };
            int base = comps(-1, -1);
            multiset<pair<int, int>> got, want;
            for (auto [a, b] : ba.bridges) got.insert({min(a, b), max(a, b)});
            for (int i = 0; i < m; i++)
                if (comps(i, -1) > base) want.insert({min(es[i].first, es[i].second), max(es[i].first, es[i].second)});
            assert(got == want);
            for (int v = 0; v < n; v++) assert(ba.isArt[v] == (comps(-1, v) > base));
        }
    }
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
