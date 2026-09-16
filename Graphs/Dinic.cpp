// Author : md_nihal
// Source/adapted-from: KACTL graph/Dinic.h (Edge struct + adjacency-of-indices, BFS level graph
// + scaling DFS with an `it[]` progress pointer per node so a saturated edge is never rescanned).
// Capacities/flow stay in `int` (== long long project-wide) deliberately: summed capacities
// through a node can exceed 2^31 even when individual edge capacities don't.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct Dinic {
    struct Edge { int to, cap, flow = 0; };
    int n;
    vector<Edge> edges;
    vector<vector<int>> adj;   // adj[u] = indices into edges[]
    vector<int> level, it;

    Dinic(int _n) : n(_n), adj(_n) {}

    // directed edge u->v with capacity cap; rcap is the reverse edge's capacity (0 unless
    // the edge is meant to be bidirectional/undirected).
    void addEdge(int u, int v, int cap, int rcap = 0) {
        adj[u].push_back((int)edges.size()); edges.push_back({v, cap});
        adj[v].push_back((int)edges.size()); edges.push_back({u, rcap});
    }

    bool bfs(int s, int t) {
        level.assign(n, -1);
        level[s] = 0;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : adj[u]) {
                auto &e = edges[id];
                if (level[e.to] == -1 && e.cap - e.flow > 0) { level[e.to] = level[u] + 1; q.push(e.to); }
            }
        }
        return level[t] != -1;
    }

    int dfs(int u, int t, int pushed) {
        if (u == t || pushed == 0) return pushed;
        for (; it[u] < (int)adj[u].size(); it[u]++) {
            int id = adj[u][it[u]];
            auto &e = edges[id];
            if (level[u] + 1 != level[e.to] || e.cap - e.flow <= 0) continue;
            int d = dfs(e.to, t, min(pushed, e.cap - e.flow));
            if (d > 0) { e.flow += d; edges[id ^ 1].flow -= d; return d; }
        }
        return 0;
    }

    int maxflow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            it.assign(n, 0);
            while (int pushed = dfs(s, t, inf)) flow += pushed;
        }
        return flow;
    }
};
/* Usage:
 *   Dinic dn(n);
 *   dn.addEdge(u, v, cap);      // directed; pass rcap too for an undirected edge
 *   dn.maxflow(s, t);
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
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
#endif
