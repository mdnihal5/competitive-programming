class LCA {
    int n, LOG;
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> up;
    vector<vector<long long>> distUp;
    vector<int> depth;

public:
    LCA(int _n) : n(_n) {
        LOG = log2(n) + 1;
        adj.resize(n);
        up.assign(n, vector<int>(LOG));
        distUp.assign(n, vector<long long>(LOG));
        depth.assign(n, 0);
    }

    void addEdge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    void init(int root = 0) {
        dfs(root, root, 0, 0);
    }

    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int k = LOG - 1; k >= 0; --k)
            if (depth[u] - (1 << k) >= depth[v])
                u = up[u][k];
        if (u == v) return u;
        for (int k = LOG - 1; k >= 0; --k) {
            if (up[u][k] != up[v][k]) {
                u = up[u][k];
                v = up[v][k];
            }
        }
        return up[u][0];
    }

    long long getDistance(int u, int v) {
        int lca = getLCA(u, v);
        return getDistToRoot(u) + getDistToRoot(v) - 2 * getDistToRoot(lca);
    }

private:
    void dfs(int v, int p, int d, long long cost) {
        up[v][0] = p;
        distUp[v][0] = cost;
        depth[v] = d;
        for (int k = 1; k < LOG; ++k) {
            up[v][k] = up[up[v][k - 1]][k - 1];
            distUp[v][k] = distUp[v][k - 1] + distUp[up[v][k - 1]][k - 1];
        }

        for (auto [to, w] : adj[v]) {
            if (to != p)
                dfs(to, v, d + 1, w);
        }
    }

    long long getDistToRoot(int v) {
        long long res = 0;
        for (int k = LOG - 1; k >= 0; --k) {
            if (v == up[v][k]) continue;
            res += distUp[v][k];
            v = up[v][k];
        }
        return res;
    }
};
