struct BinaryLift {
    int n, lg;
    vector<int> depth;
    vector<vector<int>> adj, up;

    BinaryLift(int n) : n(n), lg(__lg(n) + 1), depth(n), adj(n), up(lg, vector<int>(n, -1)) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init(int root = -1) {
        auto dfs = [&](int r) {
            vector<int> stk = {r};
            while (!stk.empty()) {
                int u = stk.back();
                stk.pop_back();
                for (int v : adj[u])
                    if (v != up[0][u]) {
                        depth[v] = depth[u] + 1;
                        up[0][v] = u;
                        stk.push_back(v);
                    }
            }
        };
        if (root != -1) dfs(root);
        else for (int u = 0; u < n; u++) if (up[0][u] == -1) dfs(u);
        for (int i = 1; i < lg; i++)
            for (int j = 0; j < n; j++)
                up[i][j] = up[i - 1][j] == -1 ? -1 : up[i - 1][up[i - 1][j]];
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        u = kthAncestor(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int i = lg - 1; i >= 0; i--)
            if (up[i][u] != up[i][v]) u = up[i][u], v = up[i][v];
        return up[0][u];
    }

    int dist(int u, int v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }

    int kthAncestor(int u, int k) {
        if (k > depth[u]) return -1;
        for (int i = 0; i < lg; i++)
            if (k >> i & 1) u = up[i][u];
        return u;
    }
};
