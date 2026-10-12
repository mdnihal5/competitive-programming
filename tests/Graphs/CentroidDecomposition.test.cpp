// CentroidDecomposition: 0-indexed connected tree, O(n log n). centroidParent[v] = parent in the centroid
// tree (-1 for its root). Walk centroidParent upwards from a node to visit its O(log n) centroid ancestors.
// Usage: cd.addEdge(u, v); cd.build(); cd.centroidParent[v];
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/Graphs/CentroidDecomposition.cpp"
/* Usage:
 *   CentroidDecomposition cd(n);
 *   cd.addEdge(u, v);           // repeat for every tree edge
 *   cd.build();
 *   cd.centroidParent[v]        // v's parent in the centroid tree (-1 for the overall root)
 *   // Typical use: for each query node, walk cd.centroidParent[] up to the root,
 *   // maintaining per-centroid aggregate structures (e.g. distances) along the way.
 */

int32_t main() {
    {
        int n = 200000;
        CentroidDecomposition cd(n);
        for (int i = 0; i + 1 < n; i++) cd.addEdge(i, i + 1);
        cd.build();
        int roots = 0;
        for (int v = 0; v < n; v++) roots += cd.centroidParent[v] == -1;
        assert(roots == 1);
    }
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
