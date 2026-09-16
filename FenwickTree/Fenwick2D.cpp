// Author : md_nihal
// Source/adapted-from: standard 2D BIT
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
struct Fenwick2D {
    int n, m;
    vector<vector<int>> t;
    Fenwick2D(int n, int m) : n(n), m(m), t(n + 1, vector<int>(m + 1, 0)) {}
    void update(int x, int y, int val) {
        for (int i = x + 1; i <= n; i += i & -i)
            for (int j = y + 1; j <= m; j += j & -j)
                t[i][j] += val;
    }
    int query(int x, int y) { // rectangle [0,x] x [0,y]
        int s = 0;
        for (int i = x + 1; i > 0; i -= i & -i)
            for (int j = y + 1; j > 0; j -= j & -j)
                s += t[i][j];
        return s;
    }
    int query(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - (x1 ? query(x1 - 1, y2) : 0)
               - (y1 ? query(x2, y1 - 1) : 0) + ((x1 && y1) ? query(x1 - 1, y1 - 1) : 0);
    }
};
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
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
#endif
