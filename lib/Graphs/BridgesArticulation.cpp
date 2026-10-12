struct BridgesArticulation {
    int n, timer = 0, edgeCount = 0;
    vector<vector<pair<int, int>>> adj;
    vector<int> disc, low, it, parentEdge;
    vector<bool> isArt;
    vector<pair<int, int>> bridges;

    BridgesArticulation(int n) : n(n), adj(n), disc(n, -1), low(n), it(n), parentEdge(n, -1), isArt(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back({v, edgeCount});
        adj[v].push_back({u, edgeCount++});
    }

    void run() {
        for (int i = 0; i < n; i++)
            if (disc[i] == -1) dfs(i);
    }

    void dfs(int s) {
        vector<int> stk = {s};
        int rootChildren = 0;
        disc[s] = low[s] = timer++;
        while (!stk.empty()) {
            int u = stk.back();
            if (it[u] < (int)adj[u].size()) {
                auto [v, id] = adj[u][it[u]++];
                if (id == parentEdge[u]) continue;
                if (disc[v] == -1) {
                    disc[v] = low[v] = timer++;
                    parentEdge[v] = id;
                    stk.push_back(v);
                } else low[u] = min(low[u], disc[v]);
            } else {
                stk.pop_back();
                if (stk.empty()) break;
                int p = stk.back();
                low[p] = min(low[p], low[u]);
                if (low[u] > disc[p]) bridges.push_back({p, u});
                if (low[u] >= disc[p]) {
                    if (p == s) rootChildren++;
                    else isArt[p] = true;
                }
            }
        }
        if (rootChildren > 1) isArt[s] = true;
    }
};
