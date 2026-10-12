struct Dinic {
    struct Edge { int to, cap, flow = 0; };
    int n;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> level, it;

    Dinic(int n) : n(n), adj(n) {}

    void addEdge(int u, int v, int cap, int rcap = 0) {
        adj[u].push_back(edges.size());
        edges.push_back({v, cap});
        adj[v].push_back(edges.size());
        edges.push_back({u, rcap});
    }

    bool bfs(int s, int t) {
        level.assign(n, -1);
        level[s] = 0;
        queue<int> q({s});
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : adj[u]) {
                auto &e = edges[id];
                if (level[e.to] == -1 && e.cap > e.flow) level[e.to] = level[u] + 1, q.push(e.to);
            }
        }
        return level[t] != -1;
    }

    int dfs(int u, int t, int f) {
        if (u == t) return f;
        int pushed = 0;
        for (int &i = it[u]; i < (int)adj[u].size(); i++) {
            int id = adj[u][i];
            auto &e = edges[id];
            if (level[e.to] != level[u] + 1 || e.cap == e.flow) continue;
            int d = dfs(e.to, t, min(f - pushed, e.cap - e.flow));
            e.flow += d, edges[id ^ 1].flow -= d, pushed += d;
            if (pushed == f) break;
        }
        return pushed;
    }

    int maxflow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            it.assign(n, 0);
            flow += dfs(s, t, inf);
        }
        return flow;
    }
};
