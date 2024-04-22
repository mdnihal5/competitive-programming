vector<int>dikstra(vector<vector<pii>>&graph, int source, int n) {
    priority_queue<pii, vector<pii>, greater<pii>>pq;
    vector<int>dist(n, inf);
    dist[source] = 0;
    pq.push({0, source});
    while (!pq.empty()) {
        auto [currDistance, node] = pq.top();
        pq.pop();
        if (currDistance != dist[node]) continue;
        for (auto [neighbour, weight] : graph[node]) {
            if (dist[neighbour] > dist[node] + weight) {
                dist[neighbour] = dist[node] + weight; pq.push({dist[neighbour], neighbour});
            }
        }
    }
    return dist;
}
