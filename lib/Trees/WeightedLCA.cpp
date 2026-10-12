struct WeightedLCA {
    int n, lg;
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> up;
    vector<int> depth, dr;

    WeightedLCA(int n) : n(n), lg(__lg(max(n, 1LL)) + 1), adj(n), up(lg, vector<int>(n)), depth(n), dr(n) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void init(int root = 0) {
        up[0][root] = root;
        vector<int> stk = {root};
        while (!stk.empty()) {
            int u = stk.back(); stk.pop_back();
            for (auto [v, w] : adj[u])
                if (v != up[0][u]) {
                    up[0][v] = u;
                    depth[v] = depth[u] + 1;
                    dr[v] = dr[u] + w;
                    stk.push_back(v);
                }
        }
        for (int i = 1; i < lg; i++)
            for (int v = 0; v < n; v++) up[i][v] = up[i - 1][up[i - 1][v]];
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int i = lg - 1; i >= 0; i--)
            if (depth[u] - (1 << i) >= depth[v]) u = up[i][u];
        if (u == v) return u;
        for (int i = lg - 1; i >= 0; i--)
            if (up[i][u] != up[i][v]) u = up[i][u], v = up[i][v];
        return up[0][u];
    }

    int dist(int u, int v) { return dr[u] + dr[v] - 2 * dr[lca(u, v)]; }
};
