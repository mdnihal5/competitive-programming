struct Fenwick2D {
    int n, m;
    vector<vector<int>> t;

    Fenwick2D(int n, int m) : n(n), m(m), t(n + 1, vector<int>(m + 1)) {}

    void update(int x, int y, int val) {
        for (int i = x + 1; i <= n; i += i & -i)
            for (int j = y + 1; j <= m; j += j & -j) t[i][j] += val;
    }

    int query(int x, int y) {
        int s = 0;
        for (int i = x + 1; i > 0; i -= i & -i)
            for (int j = y + 1; j > 0; j -= j & -j) s += t[i][j];
        return s;
    }

    int query(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};
