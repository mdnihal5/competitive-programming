struct HLD {
    int n, root;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, headOf, pos, subSize;

    HLD(int n, int root = 0) : n(n), root(root), adj(n), parent(n, -1), depth(n), heavy(n, -1), headOf(n), pos(n), subSize(n, 1) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build() {
        vector<int> order = {root};
        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];
            for (int v : adj[u])
                if (v != parent[u]) parent[v] = u, depth[v] = depth[u] + 1, order.push_back(v);
        }
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i];
            for (int v : adj[u])
                if (v != parent[u]) {
                    subSize[u] += subSize[v];
                    if (heavy[u] == -1 || subSize[v] > subSize[heavy[u]]) heavy[u] = v;
                }
        }
        int timer = 0;
        vector<pair<int, int>> stk = {{root, root}};
        while (!stk.empty()) {
            auto [u, h] = stk.back();
            stk.pop_back();
            headOf[u] = h;
            pos[u] = timer++;
            for (int v : adj[u])
                if (v != parent[u] && v != heavy[u]) stk.push_back({v, v});
            if (heavy[u] != -1) stk.push_back({heavy[u], h});
        }
    }

    int lca(int u, int v) {
        while (headOf[u] != headOf[v]) {
            if (depth[headOf[u]] < depth[headOf[v]]) swap(u, v);
            u = parent[headOf[u]];
        }
        return depth[u] < depth[v] ? u : v;
    }

    void process(int u, int v, function<void(int, int)> op) {
        while (headOf[u] != headOf[v]) {
            if (depth[headOf[u]] < depth[headOf[v]]) swap(u, v);
            op(pos[headOf[u]], pos[u]);
            u = parent[headOf[u]];
        }
        op(min(pos[u], pos[v]), max(pos[u], pos[v]));
    }
};
