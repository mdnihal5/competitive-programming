// Author : md_nihal
// Source/adapted-from: existing repo, restyled + genericized
#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(),x.end()
#define ALL(x) x.rbegin(),x.rend()
#define int long long
#define endl "\n"
const int mod = 1E9 + 7, MAX = 1E7 + 7, N = 1E5 + 5, inf = 1E18;

/* ---- SNIPPET START ---- */
template<typename T, typename F>
struct SparseTable2D {
    int n, m;
    vector<int> lg;
    vector<vector<vector<vector<T>>>> st;
    F combine;
    SparseTable2D(const vector<vector<T>> &a, F combine) : combine(combine) {
        n = a.size(); m = a[0].size();
        int Kx = __lg(max(n, 1LL)) + 1, Ky = __lg(max(m, 1LL)) + 1;
        lg.assign(max(n, m) + 1, 0);
        for (int i = 2; i < (int)lg.size(); i++) lg[i] = lg[i / 2] + 1;
        st.assign(Kx, vector<vector<vector<T>>>(Ky, vector<vector<T>>(n, vector<T>(m))));
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) st[0][0][i][j] = a[i][j];
        for (int ky = 1; ky < Ky; ky++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j + (1 << ky) <= m; j++)
                    st[0][ky][i][j] = combine(st[0][ky - 1][i][j], st[0][ky - 1][i][j + (1 << (ky - 1))]);
        for (int kx = 1; kx < Kx; kx++)
            for (int ky = 0; ky < Ky; ky++)
                for (int i = 0; i + (1 << kx) <= n; i++)
                    for (int j = 0; j + (1 << ky) <= m; j++)
                        st[kx][ky][i][j] = combine(st[kx - 1][ky][i][j], st[kx - 1][ky][i + (1 << (kx - 1))][j]);
    }
    T query(int x1, int y1, int x2, int y2) {
        int kx = lg[x2 - x1 + 1], ky = lg[y2 - y1 + 1];
        int nx = x2 - (1 << kx) + 1, ny = y2 - (1 << ky) + 1;
        return combine(combine(st[kx][ky][x1][y1], st[kx][ky][x1][ny]),
                        combine(st[kx][ky][nx][y1], st[kx][ky][nx][ny]));
    }
};
/* ---- SNIPPET END ---- */

#ifdef LOCAL_TEST
int32_t main() {
    mt19937 rng(5252);
    int n = 10, m = 10;
    vector<vector<int>> a(n, vector<int>(m));
    for (auto &row : a) for (auto &x : row) x = rng() % 50;

    SparseTable2D st(a, [](int x, int y) { return max(x, y); });

    for (int iter = 0; iter < 1000; iter++) {
        int x1 = rng() % n, y1 = rng() % m, x2 = rng() % n, y2 = rng() % m;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        int expect = INT_MIN;
        for (int i = x1; i <= x2; i++) for (int j = y1; j <= y2; j++) expect = max(expect, a[i][j]);
        assert(st.query(x1, y1, x2, y2) == expect);
    }
    cout << "OK\n";
}
#endif
