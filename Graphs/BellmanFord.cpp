// Author : md_nihal
// Source/adapted-from: KACTL graph/BellmanFord.h, extended to flood poisoned status downstream.
// The usual hand-rolled version only detects THAT a negative cycle exists somewhere; it doesn't
// tell you WHICH nodes have an undefined (-inf) shortest distance because they're reachable
// from that cycle. That distinction is exactly what a grader checks -- get it wrong and you
// report a finite distance for a node that doesn't actually have one.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct BellmanFord {
    int n;
    vector<array<int, 3>> edges;   // {u, v, w}, directed
    vector<int> dist;
    vector<bool> poisoned;         // true => dist is -infinity (reachable via a negative cycle)

    BellmanFord(int _n) : n(_n) {}

    void addEdge(int u, int v, int w) { edges.push_back({u, v, w}); }

    void run(int src) {
        dist.assign(n, inf);
        poisoned.assign(n, false);
        dist[src] = 0;

        for (int i = 0; i + 1 < n; i++)
            for (auto &e : edges) {
                int u = e[0], v = e[1], w = e[2];
                if (dist[u] != inf && dist[u] + w < dist[v]) dist[v] = dist[u] + w;
            }

        // nodes still relaxable after n-1 rounds sit on (or are directly hit by) a negative cycle
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (dist[u] != inf && dist[u] + w < dist[v]) poisoned[v] = true;
        }

        // flood the poison to everything reachable from a poisoned node (at most n-1 rounds,
        // same bound as Bellman-Ford itself: no simple path is longer than n-1 edges)
        for (int i = 0; i + 1 < n; i++) {
            bool changed = false;
            for (auto &e : edges) {
                int u = e[0], v = e[1];
                if (poisoned[u] && !poisoned[v]) { poisoned[v] = true; changed = true; }
            }
            if (!changed) break;
        }

        for (int v = 0; v < n; v++) if (poisoned[v]) dist[v] = -inf;
    }
};
/* Usage:
 *   BellmanFord bf(n);
 *   bf.addEdge(u, v, w);        // directed; repeat for every edge
 *   bf.run(src);
 *   bf.dist[v]      // inf = unreachable, -inf = poisoned by a negative cycle, else shortest dist
 *   bf.poisoned[v]  // explicit flag for the -inf case
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
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
#endif
