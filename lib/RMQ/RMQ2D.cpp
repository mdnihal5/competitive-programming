template<typename T, typename F>
struct SparseTable2D {
    int n, m;
    vector<vector<vector<vector<T>>>> st;
    F combine;

    SparseTable2D(const vector<vector<T>> &a, F combine) : n(a.size()), m(a[0].size()), combine(combine) {
        st.assign(__lg(n) + 1, vector<vector<vector<T>>>(__lg(m) + 1, a));
        for (int kx = 0; kx < (int)st.size(); kx++)
            for (int ky = 0; ky < (int)st[kx].size(); ky++) {
                if (!kx && !ky) continue;
                for (int i = 0; i + (1 << kx) <= n; i++)
                    for (int j = 0; j + (1 << ky) <= m; j++)
                        st[kx][ky][i][j] = kx
                            ? combine(st[kx - 1][ky][i][j], st[kx - 1][ky][i + (1 << (kx - 1))][j])
                            : combine(st[0][ky - 1][i][j], st[0][ky - 1][i][j + (1 << (ky - 1))]);
            }
    }

    T query(int x1, int y1, int x2, int y2) {
        int kx = __lg(x2 - x1 + 1), ky = __lg(y2 - y1 + 1);
        int nx = x2 - (1 << kx) + 1, ny = y2 - (1 << ky) + 1;
        auto &s = st[kx][ky];
        return combine(combine(s[x1][y1], s[x1][ny]), combine(s[nx][y1], s[nx][ny]));
    }
};
