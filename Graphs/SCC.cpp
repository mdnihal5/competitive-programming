// Author : md_nihal
// Source/adapted-from: KACTL graph/SCC.h (Tarjan's, single DFS folding low-link into the
// return value), reworked to an explicit-stack iterative DFS -- the recursive version blows
// the stack on a path-shaped graph once n reaches roughly 1e5-2e5, which is exactly the kind
// of "works on samples, dies on the real judge" failure the user wants to never hit mid-contest.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct SCC {
    int n, timer = 0, sccCount = 0;
    vector<vector<int>> adj;
    vector<int> disc, low, comp, stk;
    vector<bool> onStack;

    SCC(int _n) : n(_n), adj(_n), disc(_n, -1), low(_n, 0), comp(_n, -1), onStack(_n, false) {}

    void addEdge(int u, int v) { adj[u].push_back(v); }   // directed

    // components are numbered in REVERSE topological order of the condensation DAG:
    // for an edge u->v with comp[u] != comp[v], comp[u] > comp[v] always holds.
    void run() {
        for (int i = 0; i < n; i++)
            if (disc[i] == -1) dfs(i);
    }

  private:
    void dfs(int start) {
        vector<pair<int, int>> callStack = {{start, 0}};
        disc[start] = low[start] = timer++;
        stk.push_back(start);
        onStack[start] = true;

        while (!callStack.empty()) {
            int u = callStack.back().first;
            int idx = callStack.back().second;

            if (idx < (int)adj[u].size()) {
                int v = adj[u][idx];
                callStack.back().second = idx + 1;   // write back before any push/pop below
                if (disc[v] == -1) {
                    disc[v] = low[v] = timer++;
                    stk.push_back(v);
                    onStack[v] = true;
                    callStack.push_back({v, 0});
                } else if (onStack[v]) {
                    low[u] = min(low[u], disc[v]);
                }
            } else {
                callStack.pop_back();
                if (!callStack.empty()) {
                    int p = callStack.back().first;
                    low[p] = min(low[p], low[u]);
                }
                if (low[u] == disc[u]) {
                    while (true) {
                        int x = stk.back(); stk.pop_back();
                        onStack[x] = false;
                        comp[x] = sccCount;
                        if (x == u) break;
                    }
                    sccCount++;
                }
            }
        }
    }
};
/* Usage:
 *   SCC scc(n);
 *   scc.addEdge(u, v);          // directed; repeat for every edge
 *   scc.run();
 *   scc.comp[v], scc.sccCount   // component id per node, total component count
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
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
#endif
