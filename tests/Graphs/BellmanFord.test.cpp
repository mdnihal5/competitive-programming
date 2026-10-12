// BellmanFord: 0-indexed, directed edges, any weights, O(n*m). dist = inf (unreachable), -inf (reachable
// from a negative cycle, also flagged in poisoned[]), else the shortest distance. Use Dijkstra if w >= 0.
// Usage: BellmanFord bf(n); bf.addEdge(u, v, w); bf.run(src); bf.dist[v];
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Graphs/BellmanFord.cpp"
/* Usage:
 *   BellmanFord bf(n);
 *   bf.addEdge(u, v, w);        // directed; repeat for every edge
 *   bf.run(src);
 *   bf.dist[v]      // inf = unreachable, -inf = poisoned by a negative cycle, else shortest dist
 *   bf.poisoned[v]  // explicit flag for the -inf case
 */

int32_t main() {
    {
        mt19937 rng(77);
        for (int iter = 0; iter < 500; iter++) {
            int n = 1 + rng() % 6, m = rng() % 12;
            BellmanFord bf(n);
            vector<vector<int>> d(n, vector<int>(n, inf));
            for (int i = 0; i < n; i++) d[i][i] = 0;
            for (int i = 0; i < m; i++) {
                int u = rng() % n, v = rng() % n, w = (int)(rng() % 14) - 4;
                bf.addEdge(u, v, w);
                d[u][v] = min(d[u][v], w);
            }
            for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
                if (d[i][k] < inf && d[k][j] < inf) d[i][j] = min(d[i][j], max(d[i][k] + d[k][j], -inf));
            bf.run(0);
            for (int v = 0; v < n; v++) {
                bool neg = false;
                for (int k = 0; k < n; k++) if (d[0][k] < inf && d[k][k] < 0 && d[k][v] < inf) neg = true;
                assert(bf.dist[v] == (neg ? -inf : d[0][v]));
                assert(bf.poisoned[v] == neg);
            }
        }
    }
    // src=0 --1--> 1 <==negative cycle==> 2 --1--> 3   (3 is downstream of the cycle, must poison)
    // 4: unreachable.  0 --3--> 5: ordinary finite path, untouched by the cycle.
    {
        int n = 6;
        BellmanFord bf(n);
        bf.addEdge(0, 1, 1);
        bf.addEdge(1, 2, -5);
        bf.addEdge(2, 1, -5);
        bf.addEdge(2, 3, 1);
        bf.addEdge(0, 5, 3);
        bf.run(0);

        assert(bf.dist[0] == 0 && !bf.poisoned[0]);
        assert(bf.poisoned[1] && bf.dist[1] == -inf);
        assert(bf.poisoned[2] && bf.dist[2] == -inf);
        assert(bf.poisoned[3] && bf.dist[3] == -inf);   // downstream propagation, the actual gotcha
        assert(!bf.poisoned[4] && bf.dist[4] == inf);   // unreachable stays inf, not poisoned
        assert(!bf.poisoned[5] && bf.dist[5] == 3);      // untouched ordinary path
        cout << "unreachable vs poisoned distinction OK\n";
    }
    // Plain shortest paths, no negative edges at all -- must match textbook Dijkstra-style result.
    {
        int n = 5;
        BellmanFord bf(n);
        bf.addEdge(0, 1, 4); bf.addEdge(0, 2, 1);
        bf.addEdge(2, 1, 2); bf.addEdge(1, 3, 1);
        bf.addEdge(2, 3, 5); bf.addEdge(3, 4, 3);
        bf.run(0);
        assert(bf.dist[1] == 3);   // 0->2->1
        assert(bf.dist[3] == 4);   // 0->2->1->3
        assert(bf.dist[4] == 7);
        for (int v = 0; v < n; v++) assert(!bf.poisoned[v]);
        cout << "plain shortest paths OK\n";
    }
    cout << "ALL BellmanFord TESTS PASSED\n";
}
