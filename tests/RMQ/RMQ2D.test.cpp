// SparseTable2D<T,F> st(grid, combine): 0-indexed, query(x1, y1, x2, y2) inclusive corners.
// combine must be associative + idempotent (min/max/gcd). Grid must be non-empty.
// Build O(nm log n log m) time and memory, query O(1).
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/RMQ/RMQ2D.cpp"

int32_t main() {
    mt19937 rng(5252);
    for (int iter = 0; iter < 300; iter++) {
        int n = 1 + rng() % 12, m = 1 + rng() % 12;
        vector<vector<int>> a(n, vector<int>(m));
        for (auto &row : a) for (auto &x : row) x = (int)(rng() % 100) - 50;
        SparseTable2D smax(a, [](int x, int y) { return max(x, y); });
        SparseTable2D smin(a, [](int x, int y) { return min(x, y); });
        for (int x1 = 0; x1 < n; x1++) for (int x2 = x1; x2 < n; x2++)
            for (int y1 = 0; y1 < m; y1++) for (int y2 = y1; y2 < m; y2++) {
                if (rng() % 8) continue;
                int emax = -inf, emin = inf;
                for (int i = x1; i <= x2; i++) for (int j = y1; j <= y2; j++) {
                    emax = max(emax, a[i][j]); emin = min(emin, a[i][j]);
                }
                assert(smax.query(x1, y1, x2, y2) == emax);
                assert(smin.query(x1, y1, x2, y2) == emin);
            }
    }
    cout << "OK\n";
}
