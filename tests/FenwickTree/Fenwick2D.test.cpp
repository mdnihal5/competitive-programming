// Fenwick2D: 0-indexed point update, rectangle sum (inclusive corners), O(log n * log m).
// Usage: f.update(x, y, v); f.query(x1, y1, x2, y2);
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

#include "../../lib/FenwickTree/Fenwick2D.cpp"

int32_t main() {
    {
        mt19937 rng(4);
        Fenwick2D g(3, 11);
        vector<vector<int>> b(3, vector<int>(11));
        for (int it = 0; it < 500; it++) {
            int x = rng() % 3, y = rng() % 11, v = (int)(rng() % 11) - 5;
            g.update(x, y, v), b[x][y] += v;
            int x1 = rng() % 3, x2 = rng() % 3, y1 = rng() % 11, y2 = rng() % 11;
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);
            int e = 0;
            for (int i = x1; i <= x2; i++) for (int j = y1; j <= y2; j++) e += b[i][j];
            assert(g.query(x1, y1, x2, y2) == e);
        }
    }
    mt19937 rng(999);
    int n = 8, m = 8;
    Fenwick2D f(n, m);
    vector<vector<int>> a(n, vector<int>(m, 0));
    for (int iter = 0; iter < 500; iter++) {
        int x = rng() % n, y = rng() % m, v = (int)(rng() % 11) - 5;
        f.update(x, y, v); a[x][y] += v;
        int x1 = rng() % n, y1 = rng() % m, x2 = rng() % n, y2 = rng() % m;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        int expect = 0;
        for (int i = x1; i <= x2; i++) for (int j = y1; j <= y2; j++) expect += a[i][j];
        assert(f.query(x1, y1, x2, y2) == expect);
    }
    cout << "OK\n";
}
