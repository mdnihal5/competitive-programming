// SCC: 0-indexed directed graph, iterative Tarjan, O(n + m). comp[v] in [0, sccCount); ids are in
// reverse topological order of the condensation (edge u->v across components => comp[u] > comp[v]).
// Usage: scc.addEdge(u, v); scc.run(); scc.comp[v]; scc.sccCount;
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Graphs/SCC.cpp"
/* Usage:
 *   SCC scc(n);
 *   scc.addEdge(u, v);          // directed; repeat for every edge
 *   scc.run();
 *   scc.comp[v], scc.sccCount   // component id per node, total component count
 */

int32_t main() {
    {
        mt19937 rng(14);
        for (int iter = 0; iter < 500; iter++) {
            int n = 1 + rng() % 8, m = rng() % 16;
            SCC s(n);
            vector<vector<bool>> r(n, vector<bool>(n));
            for (int i = 0; i < n; i++) r[i][i] = true;
            for (int i = 0; i < m; i++) {
                int u = rng() % n, v = rng() % n;
                s.addEdge(u, v), r[u][v] = true;
            }
            for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (r[i][k] && r[k][j]) r[i][j] = true;
            s.run();
            int cnt = 0;
            for (int u = 0; u < n; u++) {
                for (int v = 0; v < n; v++) assert((s.comp[u] == s.comp[v]) == (r[u][v] && r[v][u]));
                for (int v : s.adj[u]) assert(s.comp[u] >= s.comp[v]);
                cnt = max(cnt, s.comp[u] + 1);
            }
            assert(cnt == s.sccCount);
        }
    }
    // Hand-checkable graph: two 3-cycles chained by a cross edge, plus an isolated node.
    // 0->1->2->0   (cycle A)
    // 2->3         (cross edge into cycle B)
    // 3->4->5->3   (cycle B)
    // 5->6         (isolated sink node)
    {
        SCC scc(7);
        scc.addEdge(0, 1); scc.addEdge(1, 2); scc.addEdge(2, 0);
        scc.addEdge(2, 3);
        scc.addEdge(3, 4); scc.addEdge(4, 5); scc.addEdge(5, 3);
        scc.addEdge(5, 6);
        scc.run();
        assert(scc.sccCount == 3);
        assert(scc.comp[0] == scc.comp[1] && scc.comp[1] == scc.comp[2]);
        assert(scc.comp[3] == scc.comp[4] && scc.comp[4] == scc.comp[5]);
        assert(scc.comp[0] != scc.comp[3]);
        assert(scc.comp[3] != scc.comp[6]);
        assert(scc.comp[0] != scc.comp[6]);
        cout << "hand-checked graph OK\n";
    }
    // Long path (deep chain) -- the whole reason this DFS must be iterative, not recursive.
    {
        int n = 200000;
        SCC scc(n);
        for (int i = 0; i + 1 < n; i++) scc.addEdge(i, i + 1);
        scc.run();
        assert(scc.sccCount == n);   // every node its own SCC, no cycles
        for (int i = 0; i + 1 < n; i++) assert(scc.comp[i] > scc.comp[i + 1]);
        cout << "deep chain (n=200000) OK -- no stack overflow, reverse-topo order holds\n";
    }
    // Randomized: build random SCC groups, wire them into a DAG of groups, verify grouping
    // AND the "comp[u] > comp[v] for every crossing edge" reverse-topological-order property.
    {
        mt19937 rng(2026);
        int groups = 15;
        vector<int> groupSize(groups);
        int n = 0;
        vector<int> groupStart(groups);
        for (int g = 0; g < groups; g++) {
            groupSize[g] = 1 + rng() % 5;
            groupStart[g] = n;
            n += groupSize[g];
        }
        SCC scc(n);
        // make each group a genuine cycle (or single node)
        for (int g = 0; g < groups; g++) {
            int s = groupStart[g], sz = groupSize[g];
            if (sz == 1) continue;
            for (int i = 0; i < sz; i++) scc.addEdge(s + i, s + (i + 1) % sz);
        }
        // wire groups into a DAG: only edges from lower-index group to higher-index group
        for (int g = 0; g < groups; g++)
            for (int h = g + 1; h < groups; h++)
                if (rng() % 4 == 0) {
                    int u = groupStart[g] + rng() % groupSize[g];
                    int v = groupStart[h] + rng() % groupSize[h];
                    scc.addEdge(u, v);
                }
        scc.run();
        assert(scc.sccCount == groups);
        for (int g = 0; g < groups; g++) {
            int c = scc.comp[groupStart[g]];
            for (int i = 1; i < groupSize[g]; i++) assert(scc.comp[groupStart[g] + i] == c);
        }
        // re-walk every edge and check the reverse-topo-order invariant
        for (int u = 0; u < n; u++)
            for (int v : scc.adj[u])
                if (scc.comp[u] != scc.comp[v])
                    assert(scc.comp[u] > scc.comp[v]);
        cout << "randomized DAG-of-cycles OK -- grouping + reverse-topo invariant hold\n";
    }
    cout << "ALL SCC TESTS PASSED\n";
}
