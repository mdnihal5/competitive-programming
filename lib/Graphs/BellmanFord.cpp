struct BellmanFord {
    int n;
    vector<array<int, 3>> edges;
    vector<int> dist;
    vector<bool> poisoned;

    BellmanFord(int n) : n(n) {}

    void addEdge(int u, int v, int w) { edges.push_back({u, v, w}); }

    void run(int src) {
        dist.assign(n, inf);
        poisoned.assign(n, false);
        dist[src] = 0;
        for (int i = 0; i < n; i++)
            for (auto [u, v, w] : edges)
                if (dist[u] != inf && dist[u] + w < dist[v]) {
                    dist[v] = max(dist[u] + w, -inf);
                    if (i == n - 1) poisoned[v] = true;
                }
        for (bool changed = true; changed;) {
            changed = false;
            for (auto [u, v, w] : edges)
                if (poisoned[u] && !poisoned[v]) poisoned[v] = changed = true;
        }
        for (int v = 0; v < n; v++)
            if (poisoned[v]) dist[v] = -inf;
    }
};
