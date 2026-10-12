struct FenwickRUPQ {
    int n;
    vector<int> t;

    FenwickRUPQ(int n) : n(n), t(n + 1) {}

    void add(int idx, int val) {
        for (++idx; idx <= n; idx += idx & -idx) t[idx] += val;
    }

    void update(int l, int r, int val) { add(l, val), add(r + 1, -val); }

    int query(int idx) {
        int s = 0;
        for (++idx; idx > 0; idx -= idx & -idx) s += t[idx];
        return s;
    }
};
