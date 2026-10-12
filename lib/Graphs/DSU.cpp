struct DSU {
    vector<int> par, sz;

    DSU(int n) : par(n), sz(n, 1) { iota(par.begin(), par.end(), 0); }

    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }

    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
        return true;
    }

    bool connected(int x, int y) { return find(x) == find(y); }
    int compSize(int x) { return sz[find(x)]; }
};
