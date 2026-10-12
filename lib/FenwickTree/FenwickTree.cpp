struct Fenwick {
    int n;
    vector<int> t;

    Fenwick(int n) : n(n), t(n + 1) {}

    void update(int idx, int val) {
        for (++idx; idx <= n; idx += idx & -idx) t[idx] += val;
    }

    int query(int idx) {
        int s = 0;
        for (++idx; idx > 0; idx -= idx & -idx) s += t[idx];
        return s;
    }

    int query(int l, int r) { return query(r) - query(l - 1); }

    int lower_bound(int val) {
        int pos = 0;
        for (int pw = bit_floor((unsigned long long)n); pw; pw >>= 1)
            if (pos + pw <= n && t[pos + pw] < val) pos += pw, val -= t[pos];
        return pos;
    }
};
