// Author : md_nihal
// Source/adapted-from: cp-algorithms.com centroid decomposition description -- no KACTL version
// exists for this one (confirmed absent from its graph/ and various/ folders). The step careless
// versions get wrong is recomputing subtree sizes correctly PER remaining component after each
// centroid removal, not just once for the whole original tree.
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct CentroidDecomposition {
    int n;
    vector<vector<int>> adj;
    vector<int> subSize, centroidParent;
    vector<bool> removed;

    CentroidDecomposition(int _n) : n(_n), adj(_n), subSize(_n), centroidParent(_n, -1), removed(_n, false) {}

    void addEdge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    void build() { decompose(0, -1); }

  private:
    // subtree sizes for the (not-yet-removed) component containing `start`, rooted at `start`.
    // Iterative: a single call can walk up to the whole remaining tree, and the very first
    // call (before any centroid is removed) sees the full n-node tree -- recursive post-order
    // here would blow the stack on a path-shaped input.
    int computeSize(int start) {
        vector<int> order, par(n, -1);
        vector<bool> vis(n, false);
        vector<int> stk = {start};
        vis[start] = true;
        while (!stk.empty()) {
            int u = stk.back(); stk.pop_back();
            order.push_back(u);
            for (int v : adj[u])
                if (!removed[v] && !vis[v]) { vis[v] = true; par[v] = u; stk.push_back(v); }
        }
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i];
            subSize[u] = 1;
            for (int v : adj[u])
                if (!removed[v] && par[v] == u) subSize[u] += subSize[v];
        }
        return subSize[start];
    }

    // walk from `start` toward whichever neighbour still holds > half the (remaining) tree;
    // subSize[] here is the one just computed by computeSize(start), so it's rooted at start.
    int findCentroid(int start, int treeSize) {
        int u = start, p = -1;
        while (true) {
            int nxt = -1;
            for (int v : adj[u])
                if (v != p && !removed[v] && subSize[v] > treeSize / 2) { nxt = v; break; }
            if (nxt == -1) return u;
            p = u; u = nxt;
        }
    }

    void decompose(int u, int centroidPar) {
        int treeSize = computeSize(u);
        int c = findCentroid(u, treeSize);
        centroidParent[c] = centroidPar;
        removed[c] = true;
        for (int v : adj[c])
            if (!removed[v]) decompose(v, c);   // recursion depth here is O(log n) tree levels,
    }                                            // not O(n) -- each call at least halves treeSize
};
/* Usage:
 *   CentroidDecomposition cd(n);
 *   cd.addEdge(u, v);           // repeat for every tree edge
 *   cd.build();
 *   cd.centroidParent[v]        // v's parent in the centroid tree (-1 for the overall root)
 *   // Typical use: for each query node, walk cd.centroidParent[] up to the root,
 *   // maintaining per-centroid aggregate structures (e.g. distances) along the way.
 */
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    // Hand-verified: path 0-1-2-3-4-5-6 (7 nodes). Centroid of the full path is node 3;
    // removing it leaves {0,1,2} (centroid 1) and {4,5,6} (centroid 5); removing those leaves
    // singletons. Full expected centroidParent worked out by hand alongside the algorithm.
    {
        CentroidDecomposition cd(7);
        for (int i = 0; i + 1 < 7; i++) cd.addEdge(i, i + 1);
        cd.build();
        vector<int> expected = {1, 3, 1, -1, 5, 3, 5};
        for (int i = 0; i < 7; i++) assert(cd.centroidParent[i] == expected[i]);
        cout << "hand-verified 7-node path OK\n";
    }
    // Structural invariants on random trees: exactly one root (-1), centroidParent[] forms
    // a genuine tree over all n nodes (no cycles), and depth stays O(log n) -- a buggy version
    // that fails to recompute sizes per-component degenerates toward O(n) depth.
    {
        mt19937 rng(555);
        for (int trial = 0; trial < 25; trial++) {
            int n = 50 + rng() % 900;
            CentroidDecomposition cd(n);
            for (int i = 1; i < n; i++) cd.addEdge(rng() % i, i);
            cd.build();

            int roots = 0;
            for (int v = 0; v < n; v++) if (cd.centroidParent[v] == -1) roots++;
            assert(roots == 1);

            int maxDepth = 0;
            int limit = 2 * (int)ceil(log2((double)max(n, (int)2))) + 4;
            for (int v = 0; v < n; v++) {
                int depth = 0, x = v;
                while (cd.centroidParent[x] != -1) { x = cd.centroidParent[x]; depth++; assert(depth <= limit); }
                maxDepth = max(maxDepth, depth);
            }
            assert(maxDepth <= limit);
        }
        cout << "random trees: single root + O(log n) depth invariant OK\n";
    }
    cout << "ALL CentroidDecomposition TESTS PASSED\n";
}
#endif
