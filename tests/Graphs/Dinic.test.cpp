// Dinic: 0-indexed max flow, O(V^2 E) worst case, recursion depth up to the s-t path length.
// addEdge(u, v, cap, rcap = 0): pass rcap = cap for an undirected edge. edges[id].flow = flow on edge id.
// Usage: Dinic dn(n); dn.addEdge(u, v, c); int f = dn.maxflow(s, t);
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Graphs/Dinic.cpp"
/* Usage:
 *   Dinic dn(n);
 *   dn.addEdge(u, v, cap);      // directed; pass rcap too for an undirected edge
 *   dn.maxflow(s, t);
 */

// Independent ground truth: plain Edmonds-Karp (BFS augmenting path) on an adjacency matrix,
// deliberately NOT sharing any code with Dinic above.
int bruteMaxFlow(int n, vector<array<int, 3>> &edgeList, int s, int t) {
    vector<vector<int>> cap(n, vector<int>(n, 0));
    for (auto &e : edgeList) cap[e[0]][e[1]] += e[2];
    int flow = 0;
    while (true) {
        vector<int> parent(n, -1);
        parent[s] = s;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v = 0; v < n; v++)
                if (parent[v] == -1 && cap[u][v] > 0) { parent[v] = u; q.push(v); }
        }
        if (parent[t] == -1) break;
        int aug = inf;
        for (int v = t; v != s; v = parent[v]) aug = min(aug, cap[parent[v]][v]);
        for (int v = t; v != s; v = parent[v]) { cap[parent[v]][v] -= aug; cap[v][parent[v]] += aug; }
        flow += aug;
    }
    return flow;
}

int32_t main() {
    {
        Dinic u(3);
        u.addEdge(0, 1, 5, 5), u.addEdge(1, 2, 3, 3);
        assert(u.maxflow(2, 0) == 3);
    }
    mt19937 rng(31337);
    for (int trial = 0; trial < 200; trial++) {
        int n = 4 + rng() % 6;
        int s = 0, t = n - 1;
        vector<array<int, 3>> edgeList;
        Dinic dn(n);
        int m = n + rng() % (2 * n);
        for (int e = 0; e < m; e++) {
            int u = rng() % n, v = rng() % n;
            if (u == v) continue;
            int c = 1 + rng() % 10;
            edgeList.push_back({u, v, c});
            dn.addEdge(u, v, c);
        }
        int expect = bruteMaxFlow(n, edgeList, s, t);
        int got = dn.maxflow(s, t);
        assert(got == expect);
    }
    cout << "ALL Dinic TESTS PASSED (200 random graphs vs brute-force Edmonds-Karp)\n";
}
