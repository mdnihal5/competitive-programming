struct LazySegTree {
    struct Node { int mn = 0, mx = 0, sum = 0, lazy = 0; };
    int n;
    vector<Node> t;

    LazySegTree(int n) : n(n), t(4 * n) {}

    static Node pull(const Node &a, const Node &b) { return {min(a.mn, b.mn), max(a.mx, b.mx), a.sum + b.sum, 0}; }

    void apply(int p, int l, int r, int v) {
        t[p].mn += v; t[p].mx += v; t[p].sum += v * (r - l + 1); t[p].lazy += v;
    }

    void push(int p, int l, int r) {
        int m = (l + r) / 2;
        apply(2 * p, l, m, t[p].lazy);
        apply(2 * p + 1, m + 1, r, t[p].lazy);
        t[p].lazy = 0;
    }

    void range_add(int p, int l, int r, int L, int R, int v) {
        if (R < l || r < L) return;
        if (L <= l && r <= R) return apply(p, l, r, v);
        push(p, l, r);
        int m = (l + r) / 2;
        range_add(2 * p, l, m, L, R, v);
        range_add(2 * p + 1, m + 1, r, L, R, v);
        t[p] = pull(t[2 * p], t[2 * p + 1]);
    }

    Node query(int p, int l, int r, int L, int R) {
        if (R < l || r < L) return {inf, -inf, 0, 0};
        if (L <= l && r <= R) return t[p];
        push(p, l, r);
        int m = (l + r) / 2;
        return pull(query(2 * p, l, m, L, R), query(2 * p + 1, m + 1, r, L, R));
    }

    void Add(int L, int R, int v) { range_add(1, 1, n, L, R, v); }
    int Min(int L, int R) { return query(1, 1, n, L, R).mn; }
    int Max(int L, int R) { return query(1, 1, n, L, R).mx; }
    int Sum(int L, int R) { return query(1, 1, n, L, R).sum; }
};
