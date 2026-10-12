vector<int> topoSort(int n, const vector<vector<int>> &adj) {
    vector<int> indeg(n), order;
    for (int u = 0; u < n; u++)
        for (int v : adj[u]) indeg[v]++;
    for (int i = 0; i < n; i++)
        if (!indeg[i]) order.push_back(i);
    for (int i = 0; i < (int)order.size(); i++)
        for (int v : adj[order[i]])
            if (--indeg[v] == 0) order.push_back(v);
    return (int)order.size() == n ? order : vector<int>{};
}
