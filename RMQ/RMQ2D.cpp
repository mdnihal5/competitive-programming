// https://leetcode.com/problems/largest-local-values-in-a-matrix-ii/submissions/2006296341

class RMQ2D {
    int n, m;
    vector<int> lg;
    vector<vector<vector<vector<int>>>> st;

public:
    RMQ2D(const vector<vector<int>>& a) {
        n = a.size();
        m = a[0].size();

        int Kx = __lg(n) + 1, Ky = __lg(m) + 1;

        lg.resize(max(n, m) + 1);
        for (int i = 2; i < lg.size(); i++)
            lg[i] = lg[i / 2] + 1;

        st.assign(Kx,
            vector<vector<vector<int>>>(Ky,
                vector<vector<int>>(n, vector<int>(m))));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                st[0][0][i][j] = a[i][j];

        for (int ky = 1; ky < Ky; ky++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j + (1 << ky) <= m; j++)
                    st[0][ky][i][j] = max(
                        st[0][ky - 1][i][j],
                        st[0][ky - 1][i][j + (1 << (ky - 1))]
                    );

        for (int kx = 1; kx < Kx; kx++)
            for (int ky = 0; ky < Ky; ky++)
                for (int i = 0; i + (1 << kx) <= n; i++)
                    for (int j = 0; j + (1 << ky) <= m; j++)
                        st[kx][ky][i][j] = max(
                            st[kx - 1][ky][i][j],
                            st[kx - 1][ky][i + (1 << (kx - 1))][j]
                        );
    }

    int query(int x1, int y1, int x2, int y2) {
        int kx = lg[x2 - x1 + 1];
        int ky = lg[y2 - y1 + 1];

        int nx = x2 - (1 << kx) + 1;
        int ny = y2 - (1 << ky) + 1;

        return max({
            st[kx][ky][x1][y1],
            st[kx][ky][x1][ny],
            st[kx][ky][nx][y1],
            st[kx][ky][nx][ny]
        });
    }
};
