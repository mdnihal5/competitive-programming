struct SCC {
    int n, timer = 0, sccCount = 0;
    vector<vector<int>> adj;
    vector<int> disc, low, comp, it, stk;

    SCC(int n) : n(n), adj(n), disc(n, -1), low(n), comp(n, -1), it(n) {}

    void addEdge(int u, int v) { adj[u].push_back(v); }

    void run() {
        for (int i = 0; i < n; i++)
            if (disc[i] == -1) dfs(i);
    }

    void dfs(int s) {
        vector<int> calls = {s};
        disc[s] = low[s] = timer++;
        stk.push_back(s);
        while (!calls.empty()) {
            int u = calls.back();
            if (it[u] < (int)adj[u].size()) {
                int v = adj[u][it[u]++];
                if (disc[v] == -1) {
                    disc[v] = low[v] = timer++;
                    stk.push_back(v);
                    calls.push_back(v);
                } else if (comp[v] == -1) low[u] = min(low[u], disc[v]);
            } else {
                calls.pop_back();
                if (!calls.empty()) low[calls.back()] = min(low[calls.back()], low[u]);
                if (low[u] != disc[u]) continue;
                int x;
                do {
                    x = stk.back();
                    stk.pop_back();
                    comp[x] = sccCount;
                } while (x != u);
                sccCount++;
            }
        }
    }
};
