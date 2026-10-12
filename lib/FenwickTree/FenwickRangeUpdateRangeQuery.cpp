struct FenwickRURQ {
    int n;
    vector<int> t1, t2;

    FenwickRURQ(int n) : n(n), t1(n + 1), t2(n + 1) {}

    void add(int i, int val) {
        for (int j = i; j <= n; j += j & -j) t1[j] += val, t2[j] += val * i;
    }

    void update(int l, int r, int val) { add(l + 1, val), add(r + 2, -val); }

    int prefix(int k) {
        int s1 = 0, s2 = 0;
        for (int i = k + 1; i > 0; i -= i & -i) s1 += t1[i], s2 += t2[i];
        return (k + 2) * s1 - s2;
    }

    int query(int l, int r) { return prefix(r) - prefix(l - 1); }
};
