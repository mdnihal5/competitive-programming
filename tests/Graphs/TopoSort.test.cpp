// topoSort: Kahn BFS, O(n + m). Returns a topological order of 0..n-1, or {} if the graph has a cycle.
// Usage: vector<vector<int>> adj(n); auto order = topoSort(n, adj);
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Graphs/TopoSort.cpp"
/* Usage:
 *   vector<vector<int>> adj(n);   // adj[u] = list of v with edge u->v
 *   auto order = topoSort(n, adj);
 *   if (order.empty()) { // has a cycle }
 */

int32_t main() {
    // DAG: 5 -> 2, 5 -> 0, 4 -> 0, 4 -> 1, 2 -> 3, 3 -> 1  (classic textbook example)
    {
        int n = 6;
        vector<vector<int>> adj(n);
        adj[5] = {2, 0}; adj[4] = {0, 1}; adj[2] = {3}; adj[3] = {1};
        auto order = topoSort(n, adj);
        assert((int)order.size() == n);
        vector<int> pos(n);
        for (int i = 0; i < n; i++) pos[order[i]] = i;
        for (int u = 0; u < n; u++)
            for (int v : adj[u]) assert(pos[u] < pos[v]);
        cout << "DAG OK\n";
    }
    // Cycle: 0 -> 1 -> 2 -> 0
    {
        int n = 3;
        vector<vector<int>> adj(n);
        adj[0] = {1}; adj[1] = {2}; adj[2] = {0};
        auto order = topoSort(n, adj);
        assert(order.empty());
        cout << "cycle detection OK\n";
    }
    // Long chain (depth stress) -- Kahn's is queue-based, never recursive, so this is
    // included mainly to confirm no accidental quadratic blowup, not a stack-depth concern.
    {
        int n = 200000;
        vector<vector<int>> adj(n);
        for (int i = 0; i + 1 < n; i++) adj[i] = {i + 1};
        auto order = topoSort(n, adj);
        assert((int)order.size() == n);
        for (int i = 0; i < n; i++) assert(order[i] == i);
        cout << "long chain (n=200000) OK\n";
    }
    cout << "ALL TopoSort TESTS PASSED\n";
}
