struct CentroidDecomposition {
    int n;
    vector<vector<int>> adj;
    vector<int> subSize, par, centroidParent, order;
    vector<bool> removed;

    CentroidDecomposition(int n) : n(n), adj(n), subSize(n), par(n), centroidParent(n, -1), removed(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build() { decompose(0, -1); }

    void decompose(int start, int centroidPar) {
        order = {start};
        par[start] = -1;
        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];
            subSize[u] = 1;
            for (int v : adj[u])
                if (!removed[v] && v != par[u]) par[v] = u, order.push_back(v);
        }
        int total = order.size(), c = start;
        for (int i = total - 1; i > 0; i--) subSize[par[order[i]]] += subSize[order[i]];
        for (bool moved = true; moved;) {
            moved = false;
            for (int v : adj[c])
                if (!removed[v] && v != par[c] && 2 * subSize[v] > total) {
                    c = v, moved = true;
                    break;
                }
        }
        centroidParent[c] = centroidPar;
        removed[c] = true;
        for (int v : adj[c])
            if (!removed[v]) decompose(v, c);
    }
};
