struct ToggleSegTree {
    int n;
    vector<int> sum, flip;

    ToggleSegTree(int n) : n(n), sum(4 * n), flip(4 * n) {}

    void apply(int p, int l, int r) {
        sum[p] = r - l + 1 - sum[p];
        flip[p] ^= 1;
    }

    void push(int p, int l, int r) {
        if (!flip[p]) return;
        int m = (l + r) / 2;
        apply(2 * p, l, m);
        apply(2 * p + 1, m + 1, r);
        flip[p] = 0;
    }

    void upd(int p, int l, int r, int L, int R) {
        if (R < l || r < L) return;
        if (L <= l && r <= R) return apply(p, l, r);
        push(p, l, r);
        int m = (l + r) / 2;
        upd(2 * p, l, m, L, R);
        upd(2 * p + 1, m + 1, r, L, R);
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }

    int qry(int p, int l, int r, int L, int R) {
        if (R < l || r < L) return 0;
        if (L <= l && r <= R) return sum[p];
        push(p, l, r);
        int m = (l + r) / 2;
        return qry(2 * p, l, m, L, R) + qry(2 * p + 1, m + 1, r, L, R);
    }

    void toggle(int l, int r) { upd(1, 0, n - 1, l, r); }
    int query(int l, int r) { return qry(1, 0, n - 1, l, r); }
};
