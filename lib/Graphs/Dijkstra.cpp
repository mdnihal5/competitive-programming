struct Dijkstra {
    int n;
    vector<vector<pair<int, int>>> adj;
    vector<int> dist;

    Dijkstra(int n) : n(n), adj(n) {}

    void addEdge(int u, int v, int w) { adj[u].push_back({v, w}); }

    void run(int src) {
        dist.assign(n, inf);
        dist[src] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, src});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u]) continue;
            for (auto [v, w] : adj[u])
                if (d + w < dist[v]) pq.push({dist[v] = d + w, v});
        }
    }
};
