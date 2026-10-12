struct MaxSubarraySegTree {
    struct Node { int pref, suf, best, sum; };
    int n;
    vector<Node> t;

    static Node merge(const Node &a, const Node &b) {
        return {max(a.pref, a.sum + b.pref), max(b.suf, b.sum + a.suf),
                max({a.best, b.best, a.suf + b.pref}), a.sum + b.sum};
    }

    MaxSubarraySegTree(const vector<int> &a) : n(a.size()), t(2 * n) {
        for (int i = 0; i < n; i++) t[i + n] = {a[i], a[i], a[i], a[i]};
        for (int i = n - 1; i > 0; i--) t[i] = merge(t[2 * i], t[2 * i + 1]);
    }

    void update(int i, int val) {
        for (t[i += n] = {val, val, val, val}; i > 1; i >>= 1) t[i >> 1] = merge(t[i & ~1], t[i | 1]);
    }

    int query(int l, int r) {
        Node resl = {-inf, -inf, -inf, 0}, resr = resl;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = merge(resl, t[l++]);
            if (r & 1) resr = merge(t[--r], resr);
        }
        return merge(resl, resr).best;
    }
};
