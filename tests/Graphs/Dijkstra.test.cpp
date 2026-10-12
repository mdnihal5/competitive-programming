// Dijkstra: 0-indexed, directed edges (add both ways if undirected), weights must be >= 0, O((n+m) log m).
// dist[v] = inf if unreachable.
// Usage: Dijkstra dj(n); dj.addEdge(u, v, w); dj.run(src); dj.dist[v];
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Graphs/Dijkstra.cpp"
/* Usage:
 *   Dijkstra dj(n);
 *   dj.addEdge(u, v, w);        // directed; add both ways for an undirected edge
 *   dj.run(src);
 *   dj.dist[v]      // inf = unreachable, else shortest distance from src
 */

int32_t main() {
    // classic 5-node example, hand-checked shortest distances from node 0
    Dijkstra dj(5);
    dj.addEdge(0, 1, 4); dj.addEdge(0, 2, 1);
    dj.addEdge(2, 1, 2); dj.addEdge(1, 3, 1);
    dj.addEdge(2, 3, 5); dj.addEdge(3, 4, 3);
    dj.run(0);
    vector<int> expected = {0, 3, 1, 4, 7};
    assert(dj.dist == expected);

    // unreachable node
    Dijkstra dj2(3);
    dj2.addEdge(0, 1, 1);
    dj2.run(0);
    assert(dj2.dist[2] == inf);

    // brute-force cross-check: Bellman-Ford-style full relaxation vs. Dijkstra, random small graphs
    mt19937 rng(12345);
    for (int iter = 0; iter < 200; iter++) {
        int n = 2 + rng() % 8;
        Dijkstra fast(n);
        vector<array<int, 3>> edges;
        int m = rng() % (n * (n - 1) / 2 + 1);
        for (int i = 0; i < m; i++) {
            int u = rng() % n, v = rng() % n, w = 1 + rng() % 20;
            if (u == v) continue;
            fast.addEdge(u, v, w);
            edges.push_back({u, v, w});
        }
        fast.run(0);

        vector<int> brute(n, inf);
        brute[0] = 0;
        for (int i = 0; i + 1 < n; i++)
            for (auto &e : edges)
                if (brute[e[0]] != inf && brute[e[0]] + e[2] < brute[e[1]])
                    brute[e[1]] = brute[e[0]] + e[2];

        assert(fast.dist == brute);
    }

    cout << "OK\n";
}
