class SegTree {
    int n;
    vector<int> st, lazy;

    void apply(int p, int l, int r) {
        st[p] = (r - l + 1) - st[p];
        lazy[p] ^= 1;
    }

    void push(int p, int l, int r) {
        if (!lazy[p] || l == r) return;

        int m = (l + r) >> 1;
        apply(p << 1, l, m);
        apply(p << 1 | 1, m + 1, r);
        lazy[p] = 0;
    }

    void upd(int p, int l, int r, int i, int j) {
        if (r < i || j < l) return;

        if (i <= l && r <= j) return apply(p, l, r);

        push(p, l, r);
        int m = (l + r) >> 1;
        upd(p << 1, l, m, i, j);
        upd(p << 1 | 1, m + 1, r, i, j);
        st[p] = st[p << 1] + st[p << 1 | 1];
    }

    int qry(int p, int l, int r, int i, int j) {
        if (r < i || j < l) return 0;

        if (i <= l && r <= j) return st[p];

        push(p, l, r);
        int m = (l + r) >> 1;
        return qry(p << 1, l, m, i, j)
               + qry(p << 1 | 1, m + 1, r, i, j);
    }

public:
    SegTree(int n) : n(n), st(4 * n), lazy(4 * n) {}

    void toggle(int l, int r) {
        upd(1, 0, n - 1, l, r);
    }

    int query(int l, int r) {
        return qry(1, 0, n - 1, l, r);
    }
};
